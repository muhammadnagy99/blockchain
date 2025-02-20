package models

import (
	"time"

	"github.com/google/uuid"
)

// Transaction represents a transaction record
// @Description Transaction details including sender, receiver, amount, timestamp, and signature
type Transaction struct {
	ID        string `json:"transaction_id"`
	From      string `json:"from"`
	To        string `json:"to"`
	Amount    int    `json:"amount"`
	Timestamp int64  `json:"timestamp"`
	Signature string `json:"signature"`
}

// NewTransaction creates a new transaction
func NewTransaction(from, to string, amount int,  signature string) Transaction {
	return Transaction{
		ID:        uuid.New().String(),
		From:      from,
		To:        to,
		Amount:    amount,
		Timestamp: time.Now().Unix(),
		Signature: signature,
	}
}

// SendCoinsRequest represents the request payload for sending coins
// @Description Request structure for transferring coins from one wallet to another
type SendCoinsRequest struct {
	From   string `json:"from"`
	To     string `json:"to"`
	Amount int    `json:"amount"`
}

// SendCoinsResponse represents the response after a successful transaction
// @Description Response structure containing the transaction ID of the completed transfer
type SendCoinsResponse struct {
	TransactionID string `json:"transaction_id"`
}

// GetTransactionsResponse contains a list of transactions
// @Description Response structure returning all transactions related to the authenticated wallet
type GetTransactionsResponse struct {
	Transactions []Transaction `json:"transactions"`
}
