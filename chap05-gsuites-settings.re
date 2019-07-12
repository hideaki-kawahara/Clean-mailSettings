= G Suiteでの使い方
SPFとDKIMに対応して、独自ドメインが使えるのはGoogleのG Suiteです。

== G Suiteの説明
G Suiteはコラボレーションツールです、Googleのサービスのパワーアップ版が使用できます。G SuiteのWebメールはGmailと同じです、Gmailアプリもそのまま使えます。ビジネス用ですがひとりから使用可能です、2019年現在料金は月680円（税別）からです。

G Suite用のアカウント1つから料金が発生しますが、グループアカウントと呼ばれるメーリングリストアカウントを作成することができるので、受信可能なメールアドレスは無限に作れます、送信は1アカウントに最大5つまでとなります。

== 独自ドメインをG Suiteに設定しよう
独自ドメインを所有していない人は、Google Domains(@<href>{https://domains.google/#/})で取得しましょう。



独自ドメインを所有しているなら、以下の順番でG Suiteに設定しましょう。

 1. G Suiteに契約する。（G Suiteに契約済みなら追加する）
 2. MXレコードを追加する。
 3. SPFレコードを追加する。
 4. 待つ
 5. DKIMレコードを追加する。

//raw[|latex|\pagebreak]


== G Suiteに契約する
Google Domains(@<href>{https://domains.google/#/})に接続します。
//image[dmain01][ ][scale=0.4]
@<img>{dmain01}のMANAGE MY DOMAINSを押下する。

//image[dmain02][ ][scale=0.4]
@<img>{dmain02}のG Suiteと紐づけたいドメインを選択する。

//image[dmain03][ ][scale=0.3]
@<img>{dmain03}のGET G SUITEを押下する。

//image[dmain04][ ][scale=0.5]
@<img>{dmain04}の確認ダイアログが出るのでNEXTを押下する。

//image[dmain05][ ][scale=0.4]
@<img>{dmain05}の画面でアドミンメールアドレスと名前と、非常用のメールアドレスを入力してNEXTを押下する。

//image[dmain06][ ][scale=0.4]
@<img>{dmain06}の契約プランを選択しNEXTを押下する。

//image[dmain07][ ][scale=0.4]
@<img>{dmain07}の画面を確認したらREVIEW YOUR PURCHASEを押下する。あとは通常のクレジット決済と同じです。

== G Suiteに契約済みなら追加する
G Suite(@<href>{https://gsuite.google.co.jp/intl/ja/features/})に接続します。


//image[suite01][ ][scale=0.4]
@<img>{suite01}の管理コンソールログイン画面にログインします。

//image[suite02][ ][scale=0.4]
@<img>{suite02}のドメインを押下します。

//image[suite03][ドメインの管理][scale=0.4]
@<img>{suite03}のドメインの管理を押下します。

//image[suite04][ ][scale=0.4]
@<img>{suite04}のドメイン エイリアスを追加を押下します。

//image[suite05][ ][scale=0.4]
@<img>{suite05}のドメインを選択しドメインを入力して続行してドメインの所有権を確認を押下します。@<br>{}
※画面ではエイリアスを追加となっているが、ドメインとエイリアスの選択が出ます。

//image[suite06][ ][scale=0.8]
@<img>{suite06}即座に所有権が確認されました。@<br>{}
※Google Domainsサービス以外ではDNSサーバや所有権確認ファイルのアップロードが必要となります。


== MXレコードを設定しよう
再びGoogle Domains(@<href>{https://domains.google/#/})に接続します。
//image[y01][ ][scale=0.4]
@<img>{y01}のMXレコードを設定したドメインを選択する。

//image[y02][ ][scale=0.4]
@<img>{y02}のAdd an MX record ...を押下する。

//image[y03][ ][scale=0.8]
@<img>{y03}のCustom resource recordsのレコード追加のところでMXを選択し追加する分だけ+を押下する。

//image[y04][ ][scale=0.8]
@<img>{y04}の入力欄に 優先度 メールサーバの順番に入力しADDを押下する。

//image[y05][ ][scale=0.8]
@<img>{y05}MXレコードが設定されました、反映されるまで最大2時間かかります。

//image[z01][ ][scale=0.4]
MXレコードの設定が終わったら2時間ほど待ち @<img>{suite06}の画面からGoogle MXレコードを設定を押下すると上の説明画面がでます。画面の下の方に指定された手順を完了しましたという文言があるので、そこを押下しますと、MXレコードが設定されます。

== SPFを設定しよう
//image[spf1][ ][scale=0.8]
@<img>{spf1}の画面でSPFレコードを設定して @<code>{v=spf1 include:_spf.google.com ~all} を入力してからADDを押下します。


== DKIMを設定しよう
G Suite ADMIN画面に接続する。
//image[dkim01][ ][scale=0.4]
@<img>{dkim01} G Suiteからアプリを押下する。

//image[dkim2][ ][scale=0.4]
@<img>{dkim2} G Suiteコアサービスを押下する。

//image[dkim3][ ][scale=0.5]
@<img>{dkim3} Gmailを押下する。

//image[dkim4][ ][scale=0.6]
@<img>{dkim4} メール認証(DKIM)の設定を押下する。

//image[dkim5][ ][scale=0.5]
@<img>{dkim5} メール認証(DKIM)画面から、新しいレコードを作成を押下する。

//image[dkim7][ ][scale=0.5]
@<img>{dkim7} DKIMの公開鍵が作成されます。

//image[dkim8][ ][scale=0.5]
TXTレコードを選択し @<img>{dkim7} のDNSホストの名前と、TXTレコード値をコピーして入力してADDを押下する。

//image[dkim9][ ][scale=0.5]
@<img>{dkim5}の画面を更新するとメールを認証となり、DKIMの設定が完了します。


=== 確認しよう


これまでの設定を包括的に確認できます。

こちらのURLで確認できますす。 @<href>{https://toolbox.googleapps.com/apps/checkmx/}

//image[check][ ][scale=0.4]
@<img>{check} ドメイン名を入れてチェック実行を押下するとチェックします、今回はDMARCの設定をしていないので▲の表示が出ていますが、それ以外は設定が正しいことが確認できました。

//raw[|latex|\pagebreak]

=== 送信しよう
設定したドメインから新規にユーザを作り、Gmailドメインにメールを送信して確認しましょう。

//image[OK][ヘッダー確認][scale=0.7]
受信したメールのメールヘッダーを確認すると、SPFとDKIMがともにPASSの表示が出ています、この本の目的である@<b>{きれいなメール}を送信することに成功しました。

これで、所有する独自ドメインから送信するメールが迷惑メールにされることは無いでしょう、今でも多くの企業のメールは@<b>{きれいなメール}になっていないことが多いで誇っていいと思います。

@<b>{今後もメールライフを楽しんでください。}
