package repository

import (
	"encoding/json"
	"errors"
	"log"
	"wallet-APIs/models"

	"github.com/cockroachdb/pebble"
)

var db *pebble.DB

func InitDB() error {
	var err error
	db, err = pebble.Open("wallet.db", &pebble.Options{})
	if err != nil {
		return err
	}
	log.Println("✅ PebbleDB initialized successfully!")
	return nil
}

func CloseDB() {
	if db != nil {
		db.Close()
		log.Println("🛑 PebbleDB connection closed.")
	}
}

func CreateWallet() (models.Wallet, error) {
	wallet := models.NewWallet()
	wallet.Balance = 1000

	data, err := json.Marshal(wallet)
	if err != nil {
		return models.Wallet{}, err
	}

	err = db.Set([]byte("wallet:"+wallet.ID), data, pebble.Sync)
	if err != nil {
		return models.Wallet{}, err
	}

	_, err = RecordTransaction("Reward", wallet.ID, 1000)
	if err != nil {
		log.Printf("⚠️ Failed to record reward transaction: %v", err)
	}

	log.Printf("🎁 Wallet %s created and rewarded with 1000 coins!", wallet.ID)
	return wallet, nil
}

func GetWallet(walletID string) (models.Wallet, error) {
	data, closer, err := db.Get([]byte("wallet:" + walletID))
	if err != nil {
		return models.Wallet{}, errors.New("wallet not found")
	}
	defer closer.Close()

	var wallet models.Wallet
	err = json.Unmarshal(data, &wallet)
	if err != nil {
		return models.Wallet{}, err
	}

	return wallet, nil
}

func UpdateWalletBalance(walletID string, newBalance int) error {
	wallet, err := GetWallet(walletID)
	if err != nil {
		return err
	}

	wallet.Balance = newBalance
	data, err := json.Marshal(wallet)
	if err != nil {
		return err
	}

	err = db.Set([]byte("wallet:"+walletID), data, pebble.Sync)
	return err
}
