= G Suiteでの使い方
SPFとDKIMに対応して、独自ドメインが使えるのはGoogleのG Suiteです。
== G Suiteの説明
G Suiteはコラボレーション
G SuiteのWebメールはGmailと同じです、Gmailアプリもそのまま使えます。ビジネス用ですがひとりから使用可能です、2019年現在料金は月680円（税別）からです。

G Suite用のアカウント1つから料金が発生しますが、グループアカウントと呼ばれるメーリングリストアカウントを作成することができるので、受信可能なメールアドレスは無限に作れます、送信は1アカウントに最大5つまでとなります。

== 独自ドメインをG Suiteに設定しよう
独自ドメインを所有していない人は、Google Domainsで取得しましょう。
https://domains.google/#/

独自ドメインを所有しているなら、以下の順番でG Suiteに設定しましょう。

 1. G Suiteに契約する。（G Suiteに契約済みなら追加する）
 2. MXレコードを追加する。
 3. SPFレコードを追加する。
 4. 待つ
 5. DKIMレコードを追加する。

== G Suiteに契約する



== G Suiteに契約済みなら追加する
https://gsuite.google.co.jp/intl/ja/features/
=== 設定を確認しよう
== SPFを設定しよう

https://support.google.com/a/answer/60764
v=spf1 include:_spf.google.com ~all
== DKIMを設定しよう
=== 確認しよう
https://toolbox.googleapps.com/apps/checkmx/
