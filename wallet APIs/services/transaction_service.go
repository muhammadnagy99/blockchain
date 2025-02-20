package services

import (
	"errors"
	"wallet-APIs/models"
	"wallet-APIs/repository"
)

func SendCoins(from, to string, amount int) (models.Transaction, error) {
	if amount <= 0 {
		return models.Transaction{}, errors.New("amount must be greater than zero")
	}

	senderWallet, err := repository.GetWallet(from)
	if err != nil {
		return models.Transaction{}, errors.New("sender wallet not found")
	}

	receiverWallet, err := repository.GetWallet(to)
	if err != nil {
		return models.Transaction{}, errors.New("receiver wallet not found")
	}

	if senderWallet.Balance < amount {
		return models.Transaction{}, errors.New("insufficient balance")
	}

	senderWallet.Balance -= amount
	receiverWallet.Balance += amount

	err = repository.UpdateWalletBalance(senderWallet.ID, senderWallet.Balance)
	if err != nil {
		return models.Transaction{}, err
	}

	err = repository.UpdateWalletBalance(receiverWallet.ID, receiverWallet.Balance)
	if err != nil {
		return models.Transaction{}, err
	}

	tx, err := repository.RecordTransaction(from, to, amount)
	if err != nil {
		return models.Transaction{}, err
	}

	return tx, nil
}

func GetTransactions(walletID string) ([]models.Transaction, error) {
	transactions, err := repository.GetTransactions(walletID)
	if err != nil {
		return nil, errors.New("no transactions found")
	}
	return transactions, nil
}
