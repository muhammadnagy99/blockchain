package services

import (
	"errors"
	"os"
	"time"
	"wallet-APIs/models"
	"wallet-APIs/repository"

	"github.com/golang-jwt/jwt/v4"
)

var secretKey = []byte(os.Getenv("SECRET_KEY"))

func generateToken(PublicKey string) string {
	claims := &jwt.RegisteredClaims{
		Subject:   PublicKey,
		ExpiresAt: jwt.NewNumericDate(time.Now().Add(24 * time.Hour)),
	}
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	tokenString, _ := token.SignedString(secretKey)
	return tokenString
}

func OpenWallet() (models.Wallet, string, error) {
	wallet, err := repository.CreateWallet()
	if err != nil {
		return models.Wallet{}, "", err
	}

	token := generateToken(wallet.PublicKey)
	return wallet, token, nil
}

func LoginWallet(walletID string) (string, error) {
	_, err := repository.GetWallet(walletID)
	if err != nil {
		return "", errors.New("wallet not found")
	}

	token := generateToken(walletID)
	return token, nil
}