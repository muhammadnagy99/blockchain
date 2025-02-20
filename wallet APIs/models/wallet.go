package models

import (
	"time"

	"github.com/google/uuid"
	"wallet-APIs/utils"
)

// Wallet represents a user's wallet
// @Description A wallet contains an ID, balance, and creation timestamp
type Wallet struct {
	ID        string `json:"wallet_id"`
	PublicKey string `json:"public_key"`
	Balance   int    `json:"balance"`
	CreatedAt int64  `json:"created_at"`
}

func NewWallet(secretKey string) Wallet {
	walletID := uuid.New().String()
	publicKey := utils.GeneratePublicKey(walletID)

	return Wallet{
		ID:        walletID,
		PublicKey: publicKey,
		Balance:   0,
		CreatedAt: time.Now().Unix(),
	}
}

// OpenWalletResponse represents the response after creating a new wallet
// @Description Response structure containing the wallet ID and an authentication token
type OpenWalletResponse struct {
	WalletID   string `json:"wallet_id"`
	WalletAddr string `json:"wallet_address"`
	Token      string `json:"token"`
}

// LoginRequest represents the request payload for wallet login
// @Description Request structure where the user provides their wallet ID to log in
type LoginRequest struct {
	WalletID string `json:"wallet_id"`
}

// LoginResponse represents the response after successful login
// @Description Response structure containing an authentication token for the wallet
type LoginResponse struct {
	Token string `json:"token"`
}

type WalletInfo struct {
	Balance int    `json:"balance"`
	ID      string `json:"wallet_id"`
}

type WalletAddr struct {
	ID string `json:"wallet_id"`
}
