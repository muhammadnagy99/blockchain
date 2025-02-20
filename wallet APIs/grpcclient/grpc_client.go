package grpcclient

import (
	"context"
	"fmt"
	"log"
	"time"

	pb "wallet-APIs/grpc/transaction"
	"google.golang.org/grpc"
)

type TransactionClient struct {
	client pb.TransactionServiceClient
}

func NewTransactionClient(grpcServerAddr string) *TransactionClient {
	conn, err := grpc.NewClient(grpcServerAddr, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("❌ Failed to connect to gRPC server: %v", err)
	}
	return &TransactionClient{
		client: pb.NewTransactionServiceClient(conn),
	}
}

func (tc *TransactionClient) SendTransaction(jsonData string) error {
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	request := &pb.TransactionJsonRequest{JsonData: jsonData}

	response, err := tc.client.AddTransaction(ctx, request)
	if err != nil {
		return fmt.Errorf("Failed to send transaction: %v", err)
	}

	if !response.Success {
		return fmt.Errorf("⚠️ Transaction rejected: %s", response.Message)
	}

	log.Println("✅ Transaction successfully sent to the blockchain gRPC server!")
	return nil
}
