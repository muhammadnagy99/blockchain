package middleware

import (
	"context"
	"log"
	"net/http"
	"os"
	"strings"

	"github.com/golang-jwt/jwt/v4"
)

var secretKey = []byte(os.Getenv("SECRET_KEY"))

type ContextKey string

const WalletIDKey ContextKey = "walletID"

func AuthMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		authHeader := r.Header.Get("Authorization")
		if authHeader == "" {
			log.Println("🚫 Unauthorized access attempt: Missing Authorization header")
			http.Error(w, "Missing Authorization header", http.StatusUnauthorized)
			return
		}

		tokenString := strings.TrimPrefix(authHeader, "Bearer ")
		if tokenString == "" {
			log.Println("🚫 Unauthorized access attempt: Invalid Authorization header format")
			http.Error(w, "Invalid Authorization header format", http.StatusUnauthorized)
			return
		}

		claims := &jwt.RegisteredClaims{}
		token, err := jwt.ParseWithClaims(tokenString, claims, func(token *jwt.Token) (interface{}, error) {
			return secretKey, nil
		})

		if err != nil || !token.Valid {
			log.Printf("🚫 Invalid token: %s | Error: %v\n", tokenString, err)
			http.Error(w, "Invalid or expired token", http.StatusUnauthorized)
			return
		}

		log.Printf("✅ Authenticated wallet: %s\n", claims.Subject)

		ctx := context.WithValue(r.Context(), WalletIDKey, claims.Subject)
		next.ServeHTTP(w, r.WithContext(ctx))
	})
}
