# qemu-hijack-example

Make QEMU run native shared library in emulation mode.

## Setup

### Unix

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh

./vcpkg install \
    --x-manifest-root=../scripts/vcpkg-manifest \
    --x-install-root=./installed \
    --triplet=<triplet>

# triplet:
#   Linux: `x64-linux` or `arm64-linux`
```