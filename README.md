## VF Cash nativeWallet
![VF Wallet](https://github.com/vfcash/RELEASES/blob/master/vfwallet.jpg)

## Build Target Supports
- Windows
- Linux
- OS X

`A linux build is provided in the bin directory.`

This is a Qt Creator project, Qt Creator can be setup on your native operating system and this project can be compiled with relative ease, to download the Qt Creator download the open-source option from https://www.qt.io/download

## Description
- Upon a wallet private key being entered in-order to login, it will be replaced by it's public key counterpart.
- Using the send `Priv` transactions will be securely signed locally before being sent to a remote server. This function serves as a good implementation example for Decentralised Wallet developers to implement VF Cash transactions.
- Once a transaction is made, the Transaction Explorer will display the transaction.
- Due to the project using Qt it's fairly simple to compile onto a range of different target platforms as listed above.
- Nu generated private keys are saved to `~/.vfc-keys.priv`
