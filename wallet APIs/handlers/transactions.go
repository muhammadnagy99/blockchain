package handlers

import (
	"encoding/json"
	"net/http"
	"wallet-APIs/models"
	"wallet-APIs/services"
	"wallet-APIs/middleware"
)

// SendCoinsHandler sends coins from one wallet to another
// @Summary Send coins
// @Description Transfers a specified amount from one wallet to another, requires authentication
// @Tags Transactions
// @Accept json
// @Produce json
// @Param Authorization header string true "Bearer Token"
// @Param request body models.SendCoinsRequest true "Transaction details"
// @Success 200 {object} models.SendCoinsResponse
// @Router /wallet/send [post]
func SendCoinsHandler(w http.ResponseWriter, r *http.Request) {
	var req models.SendCoinsRequest
	err := json.NewDecoder(r.Body).Decode(&req)
	if err != nil {
		http.Error(w, "Invalid request", http.StatusBadRequest)
		return
	}

	tx, err := services.SendCoins(req.From, req.To, req.Amount)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	response := models.SendCoinsResponse{
		TransactionID: tx.ID,
	}
	json.NewEncoder(w).Encode(response)
}

// GetTransactionsHandler retrieves all transactions for the authenticated wallet
// @Summary Get transactions
// @Description Returns a list of transactions related to the authenticated wallet
// @Tags Transactions
// @Accept json
// @Produce json
// @Param Authorization header string true "Bearer Token"
// @Success 200 {object} models.GetTransactionsResponse
// @Router /wallet/transactions [get]
func GetTransactionsHandler(w http.ResponseWriter, r *http.Request) {
	walletID, ok := r.Context().Value(middleware.WalletIDKey).(string)
	if !ok || walletID == "" {
		http.Error(w, "Unauthorized", http.StatusUnauthorized)
		return
	}

	transactions, err := services.GetTransactions(walletID)
	if err != nil {
		http.Error(w, "No transactions found", http.StatusNotFound)
		return
	}

	response := models.GetTransactionsResponse{
		Transactions: transactions,
	}
	json.NewEncoder(w).Encode(response)
}
