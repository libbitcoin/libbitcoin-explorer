[![Build Status](https://travis-ci.org/libbitcoin/libbitcoin_explorer.svg?branch=master)](https://travis-ci.org/libbitcoin/libbitcoin_explorer)
# Bitcoin Explorer
Bitcoin at the command line.
## Build Status
The build is failing because it exceeds the Travis timeout limit of 50 minutes.
There is not much we can do to shorten the build time while maintaining reliability.
We are looking into isolating the [ZMQ test](https://github.com/zeromq/libzmq/tree/master/tests)
compilation from the build, but this will be insufficient to complete the build.
Travis has indicated to us that a change to this limit is
[on their roadmap](https://github.com/travis-ci/travis-ci/issues/2736#issuecomment-54270410).
