# GMSAPasswordReader
Credit goes to rvazarkar <3. this is the main repo : https://github.com/rvazarkar/GMSAPasswordReader

This repo is just to have the prebuilt compiled exes to avoid manual compilation.


## Description

Reads the password blob from a GMSA account using LDAP, and parses the values into hashes for re-use.

## Compiling
Clone this project and build using Visual Studio.

## Usage
./GMSAPasswordReader --AccountName jkohler

## Previous Work and Acknowledgements
Huge thanks to [Mark Gamache](https://github.com/markgamache) for the basis of this program and doing all the hard work of figuring out the structures.

Big thanks to [Will Schroeder](https://twitter.com/harmj0y?lang=en) and [Benjamin Delpy](https://twitter.com/gentilkiwi) for the code used to generate hashes.
