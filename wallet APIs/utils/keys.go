package utils

import (
	"crypto/hmac"
	"crypto/sha256"
	"encoding/hex"
	"os"
)

// generateHMAC generates a cryptographic HMAC-SHA256 hash
func generateHMAC(secret, data string) string {
	h := hmac.New(sha256.New, []byte(secret))
	h.Write([]byte(data))
	return hex.EncodeToString(h.Sum(nil))
}

// GeneratePrivateKey creates a private key using HMAC-SHA256
func GeneratePrivateKey(walletID string) string {
	secret := os.Getenv("SECRET_KEY") // Get the secret key from environment
	return generateHMAC(secret, walletID+"private")
}

// GeneratePublicKey creates a public key from the private key
func GeneratePublicKey(walletID string) string {
	secret := os.Getenv("SECRET_KEY") // Get the secret key from environment
	return generateHMAC(secret, walletID+"public")
}
