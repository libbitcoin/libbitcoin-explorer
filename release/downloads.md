### WARNING
These binaries are provided for your convenience. We cannot and do not guarantee that they will not lose your money or compromise your privacy. You are free to inspect the source code and build it yourself. **By downloading a binary copy of BX you accept all responsibility for its use and behavior.**

### Download
Each download is a single executable file.

| OS | File | Bytes | SHA-256 | Signed |
|----|------|-------|---------|--------|
|![osx](https://github.com/libbitcoin/libbitcoin-explorer/wiki/osx.png)        | [`bx-osx-x64-mainnet-2.0.0`]()     | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![osx](https://github.com/libbitcoin/libbitcoin-explorer/wiki/osx.png)        | [`bx-osx-x64-testnet-2.0.0`]()     | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![linux](https://github.com/libbitcoin/libbitcoin-explorer/wiki/linux.png)    | [`bx-linux-x64-mainnet-2.0.0`]()   | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![linux](https://github.com/libbitcoin/libbitcoin-explorer/wiki/linux.png)    | [`bx-linux-x64-testnet-2.0.0`]()   | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![windows](https://github.com/libbitcoin/libbitcoin-explorer/wiki/windows.png)| [`bx-windows-x64-mainnet-2.0.0`]() | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![windows](https://github.com/libbitcoin/libbitcoin-explorer/wiki/windows.png)| [`bx-windows-x64-testnet-2.0.0`]() | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![windows](https://github.com/libbitcoin/libbitcoin-explorer/wiki/windows.png)| [`bx-windows-x86-mainnet-2.0.0`]() | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |
|![windows](https://github.com/libbitcoin/libbitcoin-explorer/wiki/windows.png)| [`bx-windows-x86-testnet-2.0.0`]() | `bbb` | [`hh..hh`](#hhhh) | [`ss..ss`](#ssss) |

### Integrity Validation
Validate the integrity of the download by calculating a SHA-256 hash of the file and comparing the result to that in the table above. If you do not have a previously verified version of `bx` you can use any local or online [hash computer](http://onlinemd5.com). The hash encoding is not case sensitive.

### Origin Validation
Validate the origin of the download by verifying the Bitcoin signature in the table above against the address `1GpL7EH3QFeG89mZf7dKKssYf4gjrH4mu7` and the SHA-256 hash. If you do not have a previously verified version of `bx` you can do this using the [Electrum](https://bsidebtc.com/sign-verify-message-electrum) wallet (and potentially others). The "message" to verify is the SHA-256 hash.

### Using BX to Validate Itself
With a previously-verified version of BX you can validate both the integrity and origin of the download using the following commands.

Calculate the SHA-256 hash
```sh
$ bx base16-encode < bx-osx-x64-mainnet-2.0.0 | bx sha256
```
```
ssssssss
```

Validate the Bitcoin signature
```sh
$ bx message-validate 1GpL7EH3QFeG89mZf7dKKssYf4gjrH4mu7 ssssssss hhhhhhhh
```
```
The signature is valid.
```

### Testnet vs. Mainnet
BX depends on the [libbitcoin](https://github.com/libbitcoin/libbitcoin) toolkit, which currently requires recompilation for use with [testnet](https://en.bitcoin.it/wiki/Testnet). BX also provides [configuration settings](https://github.com/libbitcoin/libbitcoin-explorer/wiki/Configuration-Settings) for testnet. Each build can self-identify as testnet vs. mainnet using the [`settings`](bx-settings) command.
```sh
$ bx settings
```
```js
settings
{
    general
    {
        network testnet
        retries 0
        wait 2000
    }
    mainnet
    {
        url tcp://obelisk.airbitz.co:9091
    }
    testnet
    {
        url tcp://obelisk-testnet.airbitz.co:9091
    }
}
```
See the value of the `settings.general.network` property above.