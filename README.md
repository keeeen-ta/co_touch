# こだち配列

## 英語入力：Optimised for Vim input

|    |    |    |    |    |    |    |    |    |    |    |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| Ｑ | Ｕ | Ｉ | Ｆ | Ｚ |    | ： | Ｖ | Ｓ | Ｒ | ； |
| Ｇ | Ａ | ， | Ｅ | Ｏ |    | Ｃ | Ｔ | ． | Ｎ | Ｊ |
| Ｂ | Ｌ | Ｍ | Ｈ | Ｗ |    | Ｘ | Ｄ | Ｐ | Ｙ | Ｋ |
|    |    | 制 | 空 | 英 |    | 日 | 削 | 改 |    |    |

|    |    |    |    |    |    |    |    |    |    |    |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| ｀ | ” | ’ | ＠ | ＾ |    | ： | ＿ | － | ＊ |    |
| ［ | （ | ？ | ｛ | ＜ |    | ＆ | ／ | ！ | ＝ | ￥ |
| ］ | ） | ＃ | ｝ | ＞ |    | ＼ | ＋ | ％ | ＄ | ～ |
|    |    | 〃 | 〃 | 〃 |    | 〃 | 〃 | 〃 |    |    |

## 日本語入力：Inspired by 薙刀式

|    |    |    |    |    |    |    |    |    |    |    |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| ← | こ | き | を | ・ |    | ： | ま | な | る | → |
| と | し | 、 | か | に |    | く | い | 。 | ん | ー |
| お | も | っ | て | は |    | つ | の | う | た | そ |
|    |    | 〃 | 〃 | 〃 |    | 〃 | 〃 | 〃 |    |    |

|    |    |    |    |    |    |    |    |    |    |    |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|    | り | え | ち |    |    |    | へ | や | さ |    |
| み | ら | れ | あ | け |    | ろ | す | れ | よ | 〜 |
| せ | ふ | ひ | わ | め |    | む | ほ | ね | ゆ | ぬ |
|    |    | 〃 | 〃 | 〃 |    | 〃 | 〃 | 〃 |    |    |

- ショートカット

|    |    |    |    |    |    |    |    |    |    |    |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|

制：Tabキー（制表キー）
空：Spaceキー（空白キー）
英：英語入力に切り替え
日：日本語入力に切り替え

## ビルド手順 (Keyball39)

### 前提

- QMK Firmware 0.22.14
- Python venv + QMK CLI
- avr-gcc

### セットアップ

```bash
# リポジトリのクローン
git clone https://github.com/Yowkees/keyball.git keyball
git clone https://github.com/qmk/qmk_firmware.git --depth 1 --recurse-submodules --shallow-submodules -b 0.22.14 qmk
git clone https://github.com/keeeen-ta/co_touch.git co_touch

# Python環境
uv venv
source .venv/bin/activate
uv pip install -r requirements.txt
uv pip install -r qmk/requirements.txt

# QMKセットアップ
qmk setup -H $(pwd)/qmk

# シンボリックリンク
ln -s $(pwd)/keyball/qmk_firmware/keyboards/keyball qmk/keyboards/keyball
ln -s $(pwd)/co_touch/keyball39 qmk/keyboards/keyball/keyball39/keymaps/co_touch
ln -s $(pwd)/co_touch/lib qmk/keyboards/keyball/lib/co_touch
```

### ビルド

パスワード機能なし:

```bash
source .venv/bin/activate
cd qmk
make SKIP_GIT=yes keyball/keyball39:co_touch
```

パスワード機能あり (KeePassXC連携):

```bash
source .venv/bin/activate
./co_touch/build.sh
```

KeePassXCのマスターパスワードを入力すると、ActiveDirectoryとKeePassXCのパスワードを取得してビルドします。パスワードはファイルに残りません。

生成物: `qmk/keyball_keyball39_co_touch.hex`
