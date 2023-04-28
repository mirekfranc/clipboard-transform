# clipboard-transform

## does the following transformations
* suse bug url to bsc#number
* bsc#number to bug url
* suse bugzilla number to bug url

* hash of a commit to upstream git url
* upstream git url to hash of a commit

## example with wl-clipboard

* wl-paste -p | clipboard-transform | wl-copy -p # https://github.com/bugaevc/wl-clipboard

## build

* ninja # requires C++20
