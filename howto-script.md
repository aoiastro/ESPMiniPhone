# AstroScript 開発ガイド

ESPMiniPhoneで動作する簡易スクリプト（.cpp）の書き方ガイドです。

## 基本仕様

スクリプトエンジンは、ファイルを1行ずつ読み込み、特定のキーワードに一致する行をコマンドとして実行します。

### 対応コマンド

| コマンド | 説明 | 例 |
| :--- | :--- | :--- |
| `M5.Lcd.fillScreen(color);` | 画面を塗りつぶします。 | `M5.Lcd.fillScreen(0x000000);` |
| `M5.Lcd.print("text");` | 文字列を表示します（改行なし）。 | `M5.Lcd.print("Hello");` |
| `M5.Lcd.println("text");` | 文字列を表示し、改行します。 | `M5.Lcd.println("World");` |
| `M5.Lcd.setTextColor(color);` | 文字色を設定します。 | `M5.Lcd.setTextColor(0xFFFFFF);` |
| `M5.Lcd.setCursor(x, y);` | 表示開始位置を設定します。 | `M5.Lcd.setCursor(10, 50);` |
| `delay(ms);` | 指定したミリ秒待機します。 | `delay(1000);` |

※ `color` は `0xRRGGBB` 形式の16進数で指定してください。

## スクリプトの例

以下の内容を `.cpp` ファイルとして保存し、GitHub等からダウンロードして実行できます。

```cpp
M5.Lcd.fillScreen(0x000000);
M5.Lcd.setTextColor(0x00FF00);
M5.Lcd.setCursor(10, 10);
M5.Lcd.println("AstroScript Demo");
delay(1000);
M5.Lcd.setTextColor(0xFFFFFF);
M5.Lcd.println("Executing task...");
delay(2000);
M5.Lcd.println("Done!");
```

## 注意事項

- インタープリタは1行単位で処理するため、1行に2つ以上のコマンドを書かないでください。
- 実行中にいずれかのボタンを押すと強制終了してApp Storeに戻ります。
