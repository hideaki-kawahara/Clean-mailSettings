= G Suiteでの使い方
SPFとDKIMに対応していて、独自ドメインが使えるのはGoogleのG Suiteです。

== G Suiteの説明
G SuiteはGoogleの各種サービスをパワーアップしたものが利用できるコラボレーションツールです。G SuiteのWebメールはGmailと同じで、Gmailアプリもそのまま使えます。ビジネス用ですがひとりから使用可能で、2019年現在料金は月680円（税別）からです。

G Suite用のアカウント1つから料金が発生しますが、グループアカウントと呼ばれるメーリングリストアカウントを作ることができるので、受信できるメールアドレスは無限に作れます。送信は1アカウントに最大5つまでです。

== 独自ドメインをG Suiteに設定しよう
独自ドメインを所有していない人は、Google Domains(@<href>{https://domains.google/#/})で取得しましょう。



独自ドメインを所有しているなら、以下の順番でG Suiteに設定しましょう。

 1. G Suiteに契約する。（G Suiteに契約済みなら追加する）
 2. MXレコードを追加する。
 3. 設定が反映するまで1時間待つ
 4. SPFレコードを追加する。
 5. 設定が反映するまで1時間待つ
 6. DKIMレコードを追加する。
 7. 設定が反映するまで1時間待つ

//raw[|latex|\pagebreak]


== G Suiteを契約する
Google Domains(@<href>{https://domains.google/#/})に接続します。
//image[dmain01][ ][scale=0.4,pos=H,border=on]
@<img>{dmain01}のMANAGE MY DOMAINSを押下します。

//image[dmain02][ ][scale=0.4,pos=H,border=on]
@<img>{dmain02}のG Suiteと紐づけたいドメインを選択します。

//image[dmain03][ ][scale=0.3,pos=H,border=on]
@<img>{dmain03}のGET G SUITEを押下します。

//image[dmain04][ ][scale=0.5,pos=H,border=on]
@<img>{dmain04}の確認ダイアログが出るのでNEXTを押下します。

//image[dmain05][ ][scale=0.4,pos=H,border=on]
@<img>{dmain05}の画面でアドミンメールアドレス、名前、非常用のメールアドレスを入力してNEXTを押下します。

//image[dmain06][ ][scale=0.4,pos=H,border=on]
@<img>{dmain06}の契約プランを選択しNEXTを押下します。

//image[dmain07][ ][scale=0.4,pos=H,border=on]
@<img>{dmain07}の画面を確認したらREVIEW YOUR PURCHASEを押下する。あとは通常の通販と同じです。

== G Suiteに追加する（契約済の場合）
G Suite(@<href>{https://gsuite.google.co.jp/intl/ja/features/})に接続します。


//image[suite01][ ][scale=0.4,pos=H,border=on]
@<img>{suite01}の管理コンソールログイン画面にログインします。

//image[suite02][ ][scale=0.4,pos=H,border=on]
@<img>{suite02}のドメインを押下します。

//image[suite03][ドメインの管理][scale=0.4,pos=H,border=on]
@<img>{suite03}のドメインの管理を押下します。

//image[suite04][ ][scale=0.4,pos=H,border=on]
@<img>{suite04}のドメイン エイリアスを追加を押下します。

//image[suite05][ ][scale=0.4,pos=H,border=on]
@<img>{suite05}のドメインを選択しドメインを入力して続行してドメインの所有権を確認を押下します。@<br>{}
※画面ではエイリアスを追加となっているが、ドメインとエイリアスの選択が出ます。

//image[suite06][ ][scale=0.8,pos=H,border=on]
@<img>{suite06}即座に所有権が確認されました。@<br>{}
※Google Domainsサービスを使用していなくて他サービスを使用しているときはDNSサーバに対して所有権確認などのDNSの設定やファイルのアップロードが必要です。


== MXレコードを設定しよう
再びGoogle Domains(@<href>{https://domains.google/#/})に接続します。
//image[y01][ ][scale=0.4,pos=H,border=on]
@<img>{y01}のMXレコードを設定したドメインを選択する。

//image[y02][ ][scale=0.4,pos=H,border=on]
@<img>{y02}のAdd an MX recordを押下します。

//image[y03][ ][scale=0.8,pos=H,border=on]
@<img>{y03}のCustom resource recordsのレコード追加のところでMXを選択し追加する分だけ+を押下します。

//image[y04][ ][scale=0.8,pos=H,border=on]
@<img>{y04}の入力欄に優先度とメールサーバの順番に入力しADDを押下します。

//image[y05][ ][scale=0.8,pos=H,border=on]
@<img>{y05}MXレコードが設定されました、反映されるまで最大2時間かかります。

//image[z01][ ][scale=0.4,pos=H,border=on]
MXレコードの設定が終わったら2時間ほど待ち @<img>{suite06}の画面からGoogle MXレコードを設定を押下すると上の説明画面がでます。画面の下の方に指定された手順を完了しましたという文言があるので、そのボタンを押下すると、MXレコードが設定されます。

== SPFを設定しよう
//image[spf1][ ][scale=0.8,pos=H,border=on]
@<img>{spf1}の画面でSPFレコードを設定して @<code>{v=spf1 include:_spf.google.com ~all} を入力してからADDを押下します。


1時間ぐらいしたら設定を以下のコマンドで確認します。

//cmd{
$ dig -t txt bright-system.dev | grep spf1
//}

このように表示されたら設定完了です。表示がないなら反映できていませんのでもう少し待ちましょう。
//cmd{
bright-system.dev.	3600	IN	TXT	"v=spf1 include:_spf.google.com ~all"
//}


== DKIMを設定しよう
G Suite ADMIN画面に接続します。
//image[dkim01][ ][scale=0.4,pos=H,border=on]
@<img>{dkim01} G Suiteからアプリを押下します。

//image[dkim2][ ][scale=0.4,pos=H,border=on]
@<img>{dkim2} G Suiteコアサービスを押下します。

//image[dkim3][ ][scale=0.5,pos=H,border=on]
@<img>{dkim3} Gmailを押下します。

//image[dkim4][ ][scale=0.6,pos=H,border=on]
@<img>{dkim4} メール認証（DKIM）の設定を押下します。

//image[dkim5][ ][scale=0.5,pos=H,border=on]
@<img>{dkim5} メール認証（DKIM）画面から、新しいレコードを作成を押下します。

//image[dkim7][ ][scale=0.5,pos=H,border=on]
@<img>{dkim7} DKIMの公開鍵が生成されます。

//image[dkim8][ ][scale=0.5,pos=H,border=on]
TXTレコードを選択し @<img>{dkim7} のDNSホストの名前と、TXTレコード値をコピーして入力してADDを押下します。


//raw[|latex|\pagebreak]

1時間ぐらいしたら設定を以下のコマンドで確認します。

//cmd{
$ dig -t txt google._domainkey.bright-system.dev | DKIM1
//}

このように表示されたら設定完了です。表示がないなら反映できていませんのでもう少し待ちましょう。
//cmd{
google._domainkey.bright-system.dev. 3588 IN TXT "v=DKIM1; k=rsa; p=<以下省略>"
//}


//image[dkim9][ ][scale=0.5,pos=H,border=on]
そのあとしらばくしてから @<img>{dkim5}の画面を更新するとMXレコードの認証となります。これでDKIMの設定が完了します。



== すべての設定を確認しよう


これまでの設定を包括的に確認できます。

こちらのURLを使い確認できますす。 @<href>{https://toolbox.googleapps.com/apps/checkmx/}

//image[check][ ][scale=0.3,pos=H,border=on]
@<img>{check} ドメイン名を入れてチェック実行を押下するとチェックします。今回はDMARCの設定をしていないので▲の表示が出ていますが、それのほかは設定が正しいこと確認できました。

== メールを送信しよう
設定したドメインから新規に受信メールユーザを作り、Gmailドメインにメールを送信して確認しましょう。

//image[OK][ヘッダー確認][scale=0.7,pos=H,border=on]
受信したメールのメールヘッダーを確認すると、SPFとDKIMがともにPASSの表示が出ています。この本の目的である@<b>{きれいなメール}を送信することに成功しました。

これで、所有する独自ドメインから送信するメールが迷惑メールにされることはないでしょう。今でも多くの企業のメールは@<b>{きれいなメール}になっていないことが多いので誇っていいと思います。

@<b>{今後もメールライフを楽しんでください。}
