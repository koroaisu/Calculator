# 電卓アプリ（Calculator）

Qt で作った GUI 電卓アプリです。

## 機能
- 四則演算（+, -, ×, ÷）
- 小数点対応
- クリア機能

## 必要な環境
- Qt 6.x 以上
- C++ 17 以上
- MinGW または MSVC（Windows）
- GCC（Linux）
- Clang（macOS）

## セットアップ
```bash
# リポジトリをクローン
git clone https://github.com/koroaisu/Calculator.git
cd Calculator

# ビルド
qmake Calculator.pro
make