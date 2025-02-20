package handlers

import (
	"encoding/json"
	"net/http"
	"wallet-APIs/models"
	"wallet-APIs/repository"
	"wallet-APIs/services"
	"wallet-APIs/middleware"
)

// OpenWalletHandler creates a new wallet
// @Summary Create a new wallet
// @Description Generates a new wallet and returns a JWT token
// @Tags Wallet
// @Accept json
// @Produce json
// @Success 200 {object} models.OpenWalletResponse
// @Router /wallet/open [post]
func OpenWalletHandler(w http.ResponseWriter, r *http.Request) {
	wallet, token, err := services.OpenWallet()
	if err != nil {
		http.Error(w, "Error creating wallet", http.StatusInternalServerError)
		return
	}

	response := models.OpenWalletResponse{
		WalletID: wallet.ID,
		Token:    token,
	}
	json.NewEncoder(w).Encode(response)
}

// LoginWalletHandler logs in an existing wallet
// @Summary Login an existing wallet
// @Description Logs in using a wallet ID and returns a JWT token
// @Tags Wallet
// @Accept json
// @Produce json
// @Param request body models.LoginRequest true "Wallet ID"
// @Success 200 {object} models.LoginResponse
// @Router /wallet/login [post]
func LoginWalletHandler(w http.ResponseWriter, r *http.Request) {
	var req models.LoginRequest
	err := json.NewDecoder(r.Body).Decode(&req)
	if err != nil {
		http.Error(w, "Invalid request", http.StatusBadRequest)
		return
	}

	token, err := services.LoginWallet(req.WalletID)
	if err != nil {
		http.Error(w, "Invalid wallet ID", http.StatusUnauthorized)
		return
	}

	response := models.LoginResponse{Token: token}
	json.NewEncoder(w).Encode(response)
}

// ReceiveCoinsHandler returns the authenticated wallet's address
// @Summary Get wallet address
// @Description Returns the wallet ID of the authenticated user
// @Tags Wallet
// @Accept json
// @Produce json
// @Param Authorization header string true "Bearer Token"
// @Success 200 {object} models.WalletAddr
// @Router /wallet/receive [get]
func ReceiveCoinsHandler(w http.ResponseWriter, r *http.Request) {
	walletID, ok := r.Context().Value(middleware.WalletIDKey).(string)
	if !ok || walletID == "" {
		http.Error(w, "Unauthorized", http.StatusUnauthorized)
		return
	}

	wallet, err := repository.GetWallet(walletID)
	if err != nil {
		http.Error(w, "Wallet not found", http.StatusNotFound)
		return
	}

	json.NewEncoder(w).Encode(map[string]string{
		"wallet_id": wallet.ID,
	})
}

// GetWalletInfoHandler returns wallet details
// @Summary Get wallet info
// @Description Returns wallet ID and balance for the authenticated user
// @Tags Wallet
// @Accept json
// @Produce json
// @Param Authorization header string true "Bearer Token"
// @Success 200 {object} models.WalletInfo
// @Router /wallet/info [get]
func GetWalletInfoHandler(w http.ResponseWriter, r *http.Request) {
	walletID, ok := r.Context().Value(middleware.WalletIDKey).(string)
	if !ok || walletID == "" {
		http.Error(w, "Unauthorized", http.StatusUnauthorized)
		return
	}

	wallet, err := repository.GetWallet(walletID)
	if err != nil {
		http.Error(w, "Wallet not found", http.StatusNotFound)
		return
	}

	json.NewEncoder(w).Encode(map[string]interface{}{
		"wallet_id": wallet.ID,
		"balance":   wallet.Balance,
	})
}