= SPFとSender ID
本章では、SPF(Sender Policy Framework)とSender IDの説明をします。これらは送信ドメイン詐称を防いで正当なドメイン名からの送信を検証する仕組みです。

== SPFとSender IDの説明
メールの基本的構造でも記載しましたが、From（送信元）とEnvelope Fromとメールーサーバのドメイン名が異なっても送信できてしまうことから、From（送信元）のメールアドレスの詐称が可能です。さらには、実在しないメールアドレスからでも送れてしまいます。

Envelope Fromはメールサーバの方が自動的に補完するので、すべて同じドメイン名からしかメール送信できないようにすれば簡単に解決するのですが、それだと利便性に影響が出ます。今となってはSMTP Authenticationなどが一般的になりましたので、それほど利便性に影響しなくなりましたが、大企業などでは外から見えるメールサーバを1つに集約をして運用する事が多く、Envelope Fromを指定してメール送信をすることが難しいです。

送信する側の対応が難しいのであれば、受信する側がなんとかすれば良いということで、@<b>{受信メールサーバがEnvelope Fromを検証する仕組みが作られました}。それはDNSサーバを使うことでした。DNSサーバにはもともとメールサーバのMXレコード@<fn>{MXレコード}が記載してあるので、メールサーバに関する情報をすでに持っていました。DNSサーバにはサーバの付加情報や関連情報を設定するTXTレコードがあったので、そこに検証するためのデータを設定するようになりました。これによりDNSサーバを使った検証システムができ上がりました。

//footnote[MXレコード][メールサーバのFQDNを記載するDNSサーバのレコード。]

=== 正当性の確認プロセス

//image[spf][SPFの確認プロセス][scale=0.8]



 1. 送信元がメールを送信する。
 2. 受信するメールサーバにリクエストがくる。
 3. 受信内容からEnvelope Fromを取得しドメイン名を取り出す。
 4. 取り出したドメイン名のSPFレコード@<fn>{SPFレコード}を取り出す。
 5. 取り出したSPFレコードにはIPアドレスまたはドメイン名（FQDN）が記載されている。ドメイン名（FQDN）ならば、そのドメイン名（FQDN）で再度SPFレコードを取り出してIPアドレスが出てくるまで繰り返す。
 6. IPアドレスとEnvelope FromのIPアドレスが一致したら認証成功とする。

//footnote[SPFレコード][SPFレコードとはDNSサーバに設定された情報で、SPFレコードを正しく取り扱えない比較的古いDNSサーバではTXTレコードに設定されてます。]




=== SPFとSender IDの違い
SPFとSender IDは検証するところが異なります。SPFはEnvelope Fromを検証しますが、Sender IDはPRA(Purported Responsible Address)を参照して検証します。Sender IDはFrom（送信元）まで検証するので、より踏み込んだ検証です。仕様公開当初はライセンス問題@<fn>{ライセンス問題}@<fn>{ひろみっちゅ}に対して多くの人が懸念を表明して、その後ライセンス問題を改修@<fn>{ライセンス問題改修}した新しい仕様が公開されましたがメールサーバのアップデートが多くなるデメリットや、大企業では運用が大変になるなどの理由であまり使われておらず、Gmailも使っていません。

//footnote[ライセンス問題][ApacheなどのオープンソースグループがSender IDに懸念を表明 @<href>{https://japan.cnet.com/article/20071784/} ]
//footnote[ひろみっちゅ][「Sender ID」はphishing詐欺防止に効果をもたらすか @<href>{http://takagi-hiromitsu.jp/diary/20040919.html#p02} ]
//footnote[ライセンス問題改修][マイクロソフト、Sender IDの修正版をIETFに再提出 @<href>{https://japan.cnet.com/article/20075391/} ]

===[column] Purported Responsible Addressについて
検証順番は以下の順番で行います。

 1. Resent-Sender
 2. Resent-From
 3. Sender
 4. From（送信元）

Resent-Senderは、メールを再送するときResent-Fromがグループの場合に再送された人として付加されます。Outlookその他のアクションにある機能で存在をしらない人が多く、ほとんど使われない。


Resent-Fromは、メールを再送するときに付加します。メールの再送することがないので、ほとんど使われない。


Senderは、実際に送信したメールアドレスがFrom（送信元）と異なるときに付加します。たとえばメーリングリストからの配信ではFrom（送信元）と異なるので付加することがあり、メルマガなどでは配信エラーの戻り先に設定する事があります。


===[/column]

//raw[|latex|\pagebreak]

== 設定説明
SPFとSender IDについて説明しましたので、続いてSPFの設定方法を紹介します。なお、Sender IDについては対応サーバが少ないこともあり、ここでは紹介しません。

//emlist[一般的な例][bash]{
v=spf1 +ip4:xxx.xxx.xxx.xxx ~all
//}
最初から順番に説明します。バージョンはSPFの仕様を定義しているRFC 4408で"@<code>{v=spf1}"と定義されており、これ以外の値を設定するとエラーとしてSPFレコード自体が破棄されてしまいます。
そのあとに続くのは定義情報です。空白で区切り複数の定義情報を記載できます。先の例の場合、@<code>{+ip4:xxx.xxx.xxx.xxx}と@<code>{~all}が定義情報です。

@<code>{+ip4:xxx.xxx.xxx.xxx} の部分はディレクティブ（directive）と呼ばれ、限定子（qualifier）と機構（mechanisms）で構成されます。形式は  @<code>{[Qualifier][Mechanism]:[Value]} です。@<br>{}
@<code>{~all} もQualifierとMechanismですが、Valueがない形式です。

Qualifierには +,-,~,?の4つの設定があります。Mechanismにマッチした結果でどのように判定するか記載します。

//table[Qualifier][Qualifierの動作]{
表記	判定	意味
------------------------------------------------------------
+	Pass	認証する。
-	Fail	認証しない。
~	SoftFail	認証しないときがある。
?	Neutral	認証されたかどうかを判断されたくない。
//}

なお+は省略できます。
定義情報は左から順番に評価されていきます。

//raw[|latex|\pagebreak]

Mechanismについて代表的なのを記載します。

//table[Mechanism][Mechanismの動作]{
表記	意味
------------------------------------------------------------
all	すべてマッチする
ip4	ValueにあるIPアドレス（IPv4）が含まれていたらマッチする。（CIDR@<fn>{CIDR}表記も可能）
ip6	ValueにあるIPアドレス（IPv6）が含まれていたらマッチする。
a	ドメイン名のAレコードが含まれていたらマッチする。
mx	ドメイン名のMXレコードが含まれていたらマッチする。
include	Valueにあるドメイン名のSPFレコードを使用する、入れ子できます。
//}

なおaは省略できます。


先ほどの例を解説すると最初の定義情報は @<code>{+ip4:xxx.xxx.xxx.xxx} なのでxxx.xxx.xxx.xxxに含まれたIPv4アドレスの場合は、送信メールサーバとして認証するという結果になります。そして次の定義情報は @<code>{~all} なので、すべての送信元について認証失敗とする場合があるという結果になります。よって全体としては『最初のIPv4アドレスはすべて認証成功とし、それ以外は認証失敗となる場合もある』ということを表します。

//emlist[G Suiteの例][bash]{
v=spf1 include:_spf.google.com ~all
//}
G Suiteでは、このような定義情報になっているが、includeにすることでG Suite利用者には最初の定義だけを記載しておくだけで、G Suiteを運営側はIPアドレスの変更を利用者に告知が不要になります。

//footnote[CIDR][CIDRとはClassless Inter-Domain Routingのこと、IPアドレスの範囲を示すための仕組みです。]

===[column] 思いのほかやっていないメールを送信しない設定

ドメイン名を取ったら取りっぱなしの方が多いですがそのまま放置するとドメイン名を迷惑メール業者が勝手に使うことがあります。それを防ぐためにも、ドメイン名を取った際にはSPFレコードにメール送信をしない設定をすることが望ましいです。

迷惑メールを送信する業者が、ドメイン名のメールサーバ名を勝手に名乗り（名乗ることだけは可能）迷惑メールを送信しても、DNSサーバ（DNSサーバは勝手に名乗れない）にメールを送信しない設定をしておくと受信メールサーバがSPFレコードを参照してFailとして判定してくれるので、そのうち迷惑メール業者がメールサーバ名を勝手に名乗らなくなります。

メールを送信しないSPFレコードの設定例を以下に示します。@<br>{}
@<code>{v=spf1 -all}

===[/column]

== 判定結果
受信サーバは @<code>{Authentication-Results}というヘッダーに@<code>{spf=}の形式でSPFレコードとEnvelope Fromの検証結果を記録します。記載される情報は次の表です。

//table[Authentication-Results][Authentication-ResultsのSPF検証結果]{
判定	意味
------------------------------------------------------------
pass	認証に成功した。
fail	認証に失敗した。（迷惑メールの可能性が高い）
softFail	認証に失敗したが送信元は~を指定しているため、失敗とするべきではない。
neutral	送信元は?を指定しているため判定すべきではない。
none	送信元はSPFレコードを公開していない。
permerror	送信元はSPFレコードの記載が間違っている。
temperror	送信元のドメインに一時的なトラブルが発生している。
//}

fail判定されたメールは迷惑メールと判定しても良いと思います。

ここで判定が難しいのは@<b>{softfail}で、SMTP Authenticationを利用していない企業でリモートワークをしているときに企業のネットワークのほかから送信になるケースがあるので、このステータスになることが多いです。また企業が配信するメルマガも@<b>{softfail}になることが多いです。重要ではないメールであり大量に来るならばブロックしても良いかと思います。


== SPFで得られる効果
送信する側がSPFを設定しないと、メール受信する側はNeutralの判定とするため、これだけではとくに大きな問題にはなりません。しかしGmailなどのサービスがNeutral判定を疑わしい判定としており、後述のDKIMの設定もしていないと、はじめにの章でも記載した通り「？」マークを出して疑わしいメールとして表示してしまいます。そのままではいつの日か迷惑メールと判定され、届かなくなってしまう可能性もあるため、SPFの設定は今すぐでもしましょう！
