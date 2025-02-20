package repository

import (
	"encoding/json"
	"errors"
	"log"
	"os"
	"wallet-APIs/models"
	"wallet-APIs/utils"
	"wallet-APIs/grpcclient"

	"github.com/cockroachdb/pebble"
)

func RecordTransaction(from, to string, amount int) (models.Transaction, error) {
	grpcServerAddr := os.Getenv("GRPC_SERVER_ADDR")
	if grpcServerAddr == "" {
		log.Fatal("❌ Missing GRPC_SERVER_ADDR in .env file")
	}

	signature := utils.GenerateSignature(from, to, amount, models.NewTransaction(from, to, amount, "").Timestamp)

	tx := models.NewTransaction(from, to, amount, signature)

	data, err := json.Marshal(tx)
	if err != nil {
		return models.Transaction{}, err
	}

	err = db.Set([]byte("tx:"+tx.ID), data, pebble.Sync)
	if err != nil {
		return models.Transaction{}, err
	}

	blockchainData := map[string]interface{}{
		"sender":         tx.From,
		"receiver":       tx.To,
		"timestamp":      tx.Timestamp,
		"amount":         float64(tx.Amount),
		"signature":      tx.Signature,
		"transaction_id": tx.ID,
	}

	jsonData, err := json.Marshal(blockchainData)
	if err != nil {
		return models.Transaction{}, err
	}

	grpcClient := grpcclient.NewTransactionClient(grpcServerAddr)

	err = grpcClient.SendTransaction(string(jsonData))
	if err != nil {
		log.Printf("⚠️ Failed to send transaction to blockchain: %v", err)
	} else {
		log.Printf("✅ Transaction sent to blockchain network: %s → %s | Amount: %d", from, to, amount)
	}

	return tx, nil
}

func GetTransactions(walletID string) ([]models.Transaction, error) {
	iter, err := db.NewIter(nil) 
	if err != nil {
		return nil, err
	}

	defer iter.Close()

	var transactions []models.Transaction

	for iter.First(); iter.Valid(); iter.Next() {
		key := iter.Key()
		if string(key[:3]) != "tx:" { 
			continue
		}

		var tx models.Transaction
		err := json.Unmarshal(iter.Value(), &tx)
		if err != nil {
			continue
		}

		if !utils.VerifySignature(tx.From, tx.To, tx.Amount, tx.Timestamp, tx.Signature) {
			log.Printf("🚨 Invalid signature detected for transaction %s!", tx.ID)
			continue
		}

		if tx.From == walletID || tx.To == walletID {
			transactions = append(transactions, tx)
		}
	}

	if len(transactions) == 0 {
		return nil, errors.New("no transactions found for this wallet")
	}

	return transactions, nil
}
