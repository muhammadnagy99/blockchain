package utils

import (
	"crypto/hmac"
	"crypto/sha256"
	"encoding/hex"
	"os"
)

func GenerateSignature(from, to string, amount int, timestamp int64) string {
	secretKey := os.Getenv("SECRET_KEY") 
	message := from + to + string(rune(amount)) + string(rune(timestamp))

	h := hmac.New(sha256.New, []byte(secretKey))
	h.Write([]byte(message))

	return hex.EncodeToString(h.Sum(nil))
}

func VerifySignature(from, to string, amount int, timestamp int64, signature string) bool {
	expectedSignature := GenerateSignature(from, to, amount, timestamp)
	return hmac.Equal([]byte(expectedSignature), []byte(signature))
}
