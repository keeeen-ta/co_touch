#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SECRETS="/mnt/c/Users/10709/AppData/Local/Temp/kb_build_secrets.tmp"

cleanup() {
    rm -f "$SECRETS"
}
trap cleanup EXIT

# パスワードをカンマ区切り16進バイト配列に変換
to_comma_hex() {
    local str="$1"
    local hex=""
    for (( i=0; i<${#str}; i++ )); do
        if [ $i -gt 0 ]; then hex+=","; fi
        hex+=$(printf '0x%02x' "'${str:$i:1}")
    done
    hex+=",0x00"
    echo "$hex"
}

# KeePassXCからパスワード取得
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "$SCRIPT_DIR/get_passwords.ps1"

mapfile -t PWS < <(tr -d '\r' < "$SECRETS")
PW1_HEX=$(to_comma_hex "${PWS[0]}")
PW2_HEX=$(to_comma_hex "${PWS[1]}")

cd "$SCRIPT_DIR/../qmk"
make SKIP_GIT=yes EXTRAFLAGS="-DSECRET_PW1_BYTES=$PW1_HEX -DSECRET_PW2_BYTES=$PW2_HEX" keyball/keyball39:co_touch
