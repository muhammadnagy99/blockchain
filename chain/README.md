**Layer 0 Blockchain Project**

This project is a custom Layer 0 blockchain implementation in C++, designed with an object-oriented approach following SOLID principles. The blockchain is not limited to Proof of Work (PoW) transactions but can be adapted for other use cases.

**The system includes:**

- Automatic Block Mining: No manual trigger is needed; blocks are mined continuously.
- Persistent Storage with RocksDB: All blockchain and transaction data is efficiently stored.
- Scalability & Modularity: Can be extended beyond PoW-based transaction visualization.

**Features**
1. Blockchain Management: Handles block creation, validation, and chain state.
2. Automatic Mining: Blocks are mined automatically without manual triggers.
3. Persistent Storage: Uses RocksDB for storing blockchain and transaction data.
4. Transaction Pool: Stores and manages pending transactions before block inclusion.
5. Serialization & Deserialization: Efficiently saves and loads blockchain data.
6. SOLID Principles: Ensures maintainability, flexibility, and modularity.
7. Multi-Purpose Use: The system can be adapted beyond Proof of Work transaction visualization.

**Installation**

1. Clone the Repository

https://github.com/muhammadnagy99/blockchain/tree/main/chain
cd chain

2. Install Dependencies

Project Dependencies: 

- CMake (>= 3.10)	
- GTest (Google Test)
- OpenSSL	
- RocksDB
- nlohmann_json (>= 3.11.2)	J
- pthread

3. Build the Project

mkdir build && cd build
cmake ..
make

4. Run the Application

./blockchain_app

**Usage**

- The blockchain automatically mines blocks.
- Transactions are stored in RocksDB and retrieved when needed.
- The system is modular and can be extended to support various consensus mechanisms.

This project is licensed under the MIT License.

**Future Improvements**
- Networking for Node Communication
- Cryptographic Signature Verification
- Consensus Optimization
