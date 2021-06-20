## VF Cash nativeWallet

## Build Targets
- Windows
- Linux
- OS X

This is a Qt Creator project, Qt Creator can be setup on your native operating system and this project can be compiled with relative ease, to download the Qt Creator download the open-source option from https://www.qt.io/download

## Instructions
- In-order to login a wallet private key must be entered, doing so will cause the input private key to be replaced by it's public key counterpart.
- Using the send `Priv` button transactions will be securely signed locally before being sent to a remote server. This function serves as a good implementation example for Decentralised Wallet developers to implement VF Cash transactions.
- Once a transaction is made, the Transaction Explorer will display the transaction.
- Due to the project using Qt it is fairly simple to compile on a range of different target platforms as listed above.
- Nu generated private keys are saved to `~/.vfc-keys.priv`
