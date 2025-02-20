package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"
	"time"

	_ "wallet-APIs/docs"
	"wallet-APIs/handlers"
	"wallet-APIs/middleware"
	"wallet-APIs/repository"

	"github.com/gorilla/mux"
	"github.com/joho/godotenv"
	httpSwagger "github.com/swaggo/http-swagger"
)

func main() {
	err := godotenv.Load()
	if err != nil {
		log.Fatal("Error loading .env file")
	}

	err = repository.InitDB()
	if err != nil {
		log.Fatalf("Failed to initialize PebbleDB: %v", err)
	}
	defer repository.CloseDB()

	r := mux.NewRouter()

	r.PathPrefix("/swagger/").Handler(httpSwagger.WrapHandler)

	r.HandleFunc("/wallet/open", handlers.OpenWalletHandler).Methods("POST")
	r.HandleFunc("/wallet/login", handlers.LoginWalletHandler).Methods("POST")

	api := r.PathPrefix("/wallet").Subrouter()
	api.Use(middleware.AuthMiddleware)
	api.HandleFunc("/info", handlers.GetWalletInfoHandler).Methods("GET")
	api.HandleFunc("/send", handlers.SendCoinsHandler).Methods("POST")
	api.HandleFunc("/receive", handlers.ReceiveCoinsHandler).Methods("GET")
	api.HandleFunc("/transactions", handlers.GetTransactionsHandler).Methods("GET")

	server := &http.Server{
		Addr:         ":8080",
		Handler:      r,
		ReadTimeout:  15 * time.Second,
		WriteTimeout: 15 * time.Second,
		IdleTimeout:  60 * time.Second,
	}

	stop := make(chan os.Signal, 1)
	signal.Notify(stop, os.Interrupt, syscall.SIGTERM)

	go func() {
		fmt.Println("🚀 Server is running on port 8080")
		if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			log.Fatalf("Server failed: %v", err)
		}
	}()

	<-stop
	fmt.Println("\n🛑 Shutting down server gracefully...")
	server.Close()
}
