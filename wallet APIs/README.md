# Blockchain Wallet API

## Overview
This project is a **secure blockchain-based wallet API** built using **Golang**. It allows users to create wallets, send and receive coins, and interact with a blockchain network via **gRPC**. Transactions are cryptographically signed and stored in **PebbleDB**, ensuring speed and security.

## Features
- **Wallet Management**: Create and authenticate wallets securely.
- **Send & Receive Coins**: Transfer funds between wallets with digital signatures.
- **Blockchain Integration**: Transactions are sent to a blockchain node via **gRPC**.
- **Digital Signatures**: Ensures transaction authenticity using **HMAC-SHA256**.
- **Persistent Storage**: Uses **PebbleDB** for fast, lightweight data storage.
- **API Security**: Implements **JWT authentication** and **middleware-based access control**.
- **Automatic Documentation**: Fully documented using **Swagger (OpenAPI)**.

## API Documentation
The complete API documentation is available on **SwaggerHub**:  
[**Wallet API Documentation**](https://app.swaggerhub.com/apis-docs/MUHAMMADNAGY71/Wallet-APIs/1.0.0#/)

## Technologies Used

### Blockchain and Cryptography
- **gRPC** – Used to communicate with the blockchain network and send transactions securely.
- **HMAC-SHA256** – Implements cryptographic signatures for transaction validation.
- **UUID-based Wallets** – Ensures unique wallet identification.

### Backend Development
- **Golang** – Used for API development with concurrency and high performance.
- **PebbleDB** – A lightweight key-value store for storing transactions and wallet data.
- **SOLID Principles** – Applied for maintainable and scalable software design.
- **REST API with Gorilla Mux** – Used for routing and request handling.

### Security and Authentication
- **JWT Authentication** – Provides secure access control for API endpoints.
- **Middleware for Authorization** – Ensures only authenticated users can perform actions.
- **Environment Variables** – Secrets such as database configurations and gRPC addresses are securely managed with `.env`.

### API Documentation
- **Swagger (OpenAPI 3.0)** – Provides interactive API documentation.
- **Auto-generated API Specs** – All endpoints, requests, and responses are documented.

## API Endpoints

### Wallet Management
| Method | Endpoint | Description | Authentication |
|--------|---------|-------------|----------------|
| POST | `/wallet/open` | Creates a new wallet and returns a JWT token | No |
| POST | `/wallet/login` | Logs in with a wallet ID and returns a JWT token | No |

### Transaction Management
| Method | Endpoint | Description | Authentication |
|--------|---------|-------------|----------------|
| POST | `/wallet/send` | Sends coins from one wallet to another | Yes |
| GET | `/wallet/transactions` | Retrieves all transactions for the authenticated wallet | Yes |

### Wallet Information
| Method | Endpoint | Description | Authentication |
|--------|---------|-------------|----------------|
| GET | `/wallet/receive` | Returns the wallet address of the authenticated user | Yes |
| GET | `/wallet/info` | Retrieves wallet ID and balance | Yes |



### License
This project is licensed under the MIT License.
