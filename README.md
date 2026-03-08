# ESPMiniPhone

M5StickC Plus2に対応した、スマートフォン風UIを持つ多機能ファームウェアです。

## 特徴

- **WiFi接続管理**: 
    - 起動時に50秒のタイムアウト付き自動接続。
    - 「Wi-Fi Connection」メニューからAPモードを起動し、モバイル端末から`m5.local`（またはIP直接）で接続して設定可能。
- **App Store**: 
    - GitHubなどの直リンクからスクリプト（.cpp）をダウンロード。
    - 独自のスクリプトエンジン（AstroScript）により、その場で実行可能。
- **スマートフォン風UI**:
    - ボタンA（正面）：決定
    - ボタンB（側面）：カーソル移動
    - ダークモード調のプレミアムなデザイン。
- **LittleFS**: 設定情報やアプリのバイナリ（スクリプト）を永続保存。

## ハードウェア構成

- **本体**: M5StickC Plus2
- **ボード設定**: `esp32dev` (PlatformIO)
- **ディスプレイ**: 1.14インチ 135x240 TFT

## インストール

1. PlatformIO IDEをインストール。
2. 本プロジェクトを開き、`pio run -t upload` を実行。

## 使い方

1. **WiFi設定**: ホームで「Wi-Fi Connection」を選択（Bで移動、Aで決定）し、APモードを開始。スマホでSSID `ESPMiniPhone-Config` に接続して設定。
2. **アプリの使用**: 「App Store」でアプリを選択し、ダウンロード＆実行。

## ライセンス

MIT
