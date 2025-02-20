package repository

import (
	"encoding/json"
	"errors"
	"log"
	"time"
	"wallet-APIs/models"
	"wallet-APIs/utils"

	"github.com/cockroachdb/pebble"
	"github.com/google/uuid"
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
	walletID := uuid.New().String()
	publicKey := utils.GeneratePublicKey(walletID)  
	privateKey := utils.GeneratePrivateKey(walletID) 

	wallet := models.Wallet{
		ID:        walletID,
		PublicKey: publicKey,
		Balance:   1000,
		CreatedAt: time.Now().Unix(),
	}

	data, err := json.Marshal(wallet)
	if err != nil {
		return models.Wallet{}, err
	}

	err = db.Set([]byte("wallet:"+wallet.ID), data, pebble.Sync)
	if err != nil {
		return models.Wallet{}, err
	}

	err = db.Set([]byte("publickey:"+publicKey), []byte(wallet.ID), pebble.Sync)
	if err != nil {
		log.Printf("⚠️ Failed to store public key for verification: %v", err)
	}

	err = db.Set([]byte("privatekey:"+privateKey), []byte(wallet.ID), pebble.Sync)
	if err != nil {
		log.Printf("⚠️ Failed to store public key for verification: %v", err)
	}

	_, err = RecordTransaction("Reward", wallet.PublicKey, 1000)
	if err != nil {
		log.Printf("⚠️ Failed to record reward transaction: %v", err)
	}

	log.Printf("🎁 Wallet %s created with public key %s and rewarded with 1000 coins!", wallet.ID, wallet.PublicKey)
	log.Printf("🔒 Private Key (not stored): %s", privateKey)

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

func GetWalletByPublicKey(publicKey string) (models.Wallet, error) {
	walletIDBytes, closer, err := db.Get([]byte("publickey:" + publicKey))
	if err != nil {
		return models.Wallet{}, errors.New("wallet not found")
	}
	defer closer.Close()

	walletID := string(walletIDBytes)

	return GetWallet(walletID)
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
