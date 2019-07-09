= SPFとSender ID
SPF(Sender Policy Framework)とSender IDの説明をします。送信ドメイン詐称を防いで正当なドメイン名からの送信を検証する仕組みです。

== SPFの説明
メールの基本的構造でも記載しましたが、From(送信元)とEnvelope Fromとメールーサーバのドメイン名が異なって送信しても問題ないことから、From(送信元)のメールアドレスの詐称が可能です、実在しないメールアドレスからでも送れます。

Envelope Fromはメールサーバの方が自動的に補完するので、全て同じドメイン名からしかメール送信できないようにすれば簡単に解決するのですが、それだと利便性が犠牲になります、今となってはSMTP Authenticationなどが一般的になりましたので、それほど利便性に影響しなくなりましたが、大企業などでは外から見えるメールサーバを一つに集約をして運用する事が多く、Envelope Fromを指定してメール送信をすることが不可能です。

送信する側の対応が難しいのであれば、受信する側がなんとかすれば良いということで、受信メールサーバがEnvelope Fromを検証する仕組みが作られました、それはDNSサーバを使うことでした。DNSサーバは元々メールサーバのMXレコード@<fn>{MXレコード}が記載さておりました、メールサーバに関する情報が記載されておりましたのでデータを追加する流れになりました、既存のMXレコードに入れるのは非対応メールサーバに影響があるから新たなレコードを用意されました、これによりDNSサーバを使った検証システムが出来上がりました。

ここに図が入る

//footnote[MXレコード][MXレコードとはメールサーバのFQDNを記載するDNSサーバのレコードです。]

=== 正当性の確認プロセス

 1. メールサーバに送信リクエストがくる。
 2. 受信内容からEnvelope Fromを取得しドメイン名を取り出す。
 3. 取り出したドメイン名のSPFレコード@<fn>{SPFレコード}を取り出す。
 4. 取り出したSPFレコードにはIPアドレスまたはドメイン名(FQDN)が記載されています。
 5. ドメイン名(FQDN)だったら、そのドメイン名(FQDN)で再度SPFレコードを取り出してIPアドレスが出てくるまで繰り返す。
 6. IPアドレスとEnvelope FromのIPアドレスが一致したら認証成功とする。

//footnote[SPFレコード][SPFレコードとはDNSサーバに設定された情報です、非対応のDNSサーバはTXTレコードに設定されてます、テキストデータが設定されて誰でも参照できます]




=== SPFとSender IDの違い
SPFとSender IDは検証するところが異なります、SPFはEnvelope Fromを検証しますが、Sender IDはPRA(Purported Responsible Address)のを参照して検証します。Sender IDはFrom(送信元)まで検証するので、より踏み込んだ検証となりますが、仕様公開当初はライセンス問題@<fn>{ライセンス問題}が存在して多くの人が懸念を表明して、その後ライセンス問題を修正@<fn>{ライセンス問題修正}しましたがメールサーバの修正が多くなるや、大企業などでは運用が大変になるなどの理由であまり使われいません、Gmailも使っていません。

//footnote[ライセンス問題][ApacheなどのオープンソースグループがSender IDに懸念を表明 @<href>{https://japan.cnet.com/article/20071784/} ]
//footnote[ライセンス問題修正][マイクロソフト、Sender IDの修正版をIETFに再提出 @<href>{https://japan.cnet.com/article/20075391/} ]


===[column] Purported Responsible Addressについて
検証順番は以下の順番で行います。

 1. Resent-Sender
 2. Resent-From
 3. Sender
 4. From（送信元）

Resent-Senderについて、Resent-Fromがグループのときにメールを再送するときに、実際に再送された人として付加される、メールの再送を使うことがないので、ほとんど使われない。


Resent-Fromについて、メールを再送するときに付加される、メールの再送することが無いので、ほとんど使われない。


Senderについて、実際に送信したメールアドレスがFrom（送信元）と異なるときに付加する、例えばメーリングリストからの配信ではFrom（送信元）と異なるので付加することがある、メルマガなどでは配信エラーの戻り先に設定する事がある。


===[/column]


== 設定説明
SPFの設定説明をします、Sender IDについては対応サーバが少ないので記載しません。

//emlist[一般的な例][bash]{
v=spf1 +ip4:xxx.xxx.xxx.xxx ~all
//}
最初のフィールドはバージョン情報になります。@<code>{v=spf1}と書きます、それ以外はエラーになります。
次のフィールドは定義情報になります、空白で区切ることで複数の定義情報を記載できます。@<code>{+ip4:xxx.xxx.xxx.xxx}と@<code>{~all}が定義情報になります。

@<code>{+ip4:xxx.xxx.xxx.xxx} はQualifierとMechanismになります。形式は  @<code>{[Qualifier][Mechanism]:[Value]} のようになります。@<br>{}
@<code>{~all} もQualifierとMechanismになりますが、Valueが無い形式です。

定義情報は左から順番に評価されていきます。

Qualifierについて +,-,~,?の4つの設定があります。Mechanismにマッチした結果でどのように判定するか記載します。

//table[Qualifier][Qualifierの動作]{
表記	判定	意味
------------------------------------------------------------
+	Pass	認証します。
-	Fail	認証しない。
~	SoftFail	認証しないときがある。
?	Neutral	どっちもしない。
//}

なお+は省略可能です。

Mechanismについて代表的なのをあげる。

//table[Mechanism][Mechanismの動作]{
表記	意味
------------------------------------------------------------
all	全てマッチする
ip4	ValueにあるIPアドレス(IPv4)が含まれていたらマッチする。(CIDR@<fn>{CIDR}可能)
ip6	ValueにあるIPアドレス(IPv6)が含まれていたらマッチする。
a	ドメイン名のAレコードが含まれていたらマッチする。
mx	ドメイン名のMXレコードが含まれていたらマッチする。
include	Valueにあるドメイン名のSPFレコードを使用する、入れ子可能です。
//}

なおaは省略可能です。

//footnote[CIDR][CIDRとはClassless Inter-Domain Routingのこと、IPアドレスの範囲を示すための仕組みです]

先ほど例を解説すると 最初の定義情報は @<code>{+ip4:xxx.xxx.xxx.xxx} なのでValueに指定されたIPアドレスを認証するとなるのでメールを認証するになる。そして次の定義情報は @<code>{~all} になるので全てマッチするのを認証しないときがあるという意味になるので、最初に指定されたIPアドレス以外のメールは認証をしないときがあるという動きになります。

//emlist[G Suiteの例][bash]{
v=spf1 include:_spf.google.com ~all
//}
G Suiteでは、このような定義情報になっているが、includeは入れ子になっております。最終的には+ip4のValueまで到達します。includeにすることでG Suite利用者には最初の定義だけを示しておくだけで、IPアドレスのメンテナンスで設定値の変更が自由になります。

===[column] 意外としていないメールを送信しない設定

ドメイン名を取得したら取得したままという方が多いですが、取得したドメイン名が汚染されることを防ぐためにも@<b>{SPFレコードにメール送信をしない設定}をすることが望ましいです。

迷惑メールを送信する業者が、取得したメールサーバ名を勝手に名乗り（名乗ることだけは可能）迷惑メールを送信しても、DNSサーバ(DNSサーバは勝手に名乗れない)にメールを送信しない設定をしておくと、受信メールサーバがSPFレコードを参照してFailとして判定してくれるので、そのうち迷惑メール業者がメールサーバ名を勝手に名乗らなくなります。

メールを送信しないSPFレコードの設定例を以下に示します。@<br>{}
@<code>{v=spf1 -all}

===[/column]


== SPFで得られる効果
送信する側がSPFを設定しないと、メール受信する側はNeutralの判定とするが、これだけでは特に大きな問題にはならない。しかしGmailなどのサービスがNeutral判定を疑わしい判定としており、いつの日か迷惑メールと判定する可能性があります。
