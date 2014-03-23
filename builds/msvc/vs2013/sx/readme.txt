This library does not export any symbols.
As a result its output can only be linked statically.
We are maintaining the dynamic builds in anticipation of implementing export definitions.
Dynamic solutions will fail to locate the expected import lib.

NEXT: Build Obelisk libraries and link to sx_wallet
THEN: Try to debug libwallet and sx_wallet and then build other dependencies for v120 as necessary.
FINA: Update all zmmq builds and add nuget packaging.

Adopted convention of linking CRT static for static libs and CRT dynamic for dynamic libs, need to verify other libs practice.