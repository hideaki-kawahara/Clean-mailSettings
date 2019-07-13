= DKIM
DKIM(Domainkeys Identified Mail)の説明をします、SPFと似ていますが電子署名（参照：@<hd>{電子署名}）で認証する仕組みです。送信ドメイン詐称を防いで正当なドメイン名からの送信を検証します。

== 電子署名
DKIMでは公開鍵暗号方式@<fn>{PKI}の仕組みを使っているので電子署名の仕組みを簡単におさらいします。公開鍵暗号方式は2種類の機能を持っています、それが暗号化と電子署名です、どちらもあらかじめ対となる秘密鍵@<fn>{秘密鍵}と公開鍵@<fn>{公開鍵}を用意します。

//image[encryption][Webでの暗号化の概念図][scale=0.5]

公開鍵を使って暗号化するのはWebではよく使われます。

暗号化では、データをもらう人が秘密鍵と公開鍵を生成します。そのあとデータを送信してもらう人に公開鍵を渡して、その公開鍵でデータを暗号化してもらいます。暗号化したデータを受信して所有している秘密鍵で復号化します、@<b>{秘密鍵は作った人しか所有していないので、その人しかデータを読むことができません、これが暗号化です}。

//image[signature][電子署名の概念図][scale=0.7]

秘密鍵を使って暗号化するのは電子署名です。

電子署名では、データを送信する人が秘密鍵と公開鍵を生成します。そのあとデータを秘密鍵で暗号化してデータを送信します、この暗号化されたデータは公開鍵で復号化できるので公開鍵を持っていれば誰でも復号化できます、@<b>{暗号化できるのは秘密鍵を所有している人だけなので秘密鍵を持っていることが検証できます、これが電子署名です}。

//footnote[PKI][公開鍵暗号方式(Public Key Infrastructure)は暗号化・符号化において別の鍵を使う方式、秘密鍵と公開鍵を生成する、一方の鍵で暗号化したら対となるもう一方の鍵でしか復号化できない。]
//footnote[秘密鍵][秘密鍵とは、公開鍵暗号方式における一対の鍵、所有者が保持するされるもの、対になる公開鍵でしか復号化できない。]
//footnote[公開鍵][公開鍵とは、公開鍵暗号方式における一対の鍵、所有者から公開されるもの、対になる秘密鍵でしか復号化できない。]


== DKIMの説明
DKIMはSPFと同じようにEnvelope Fromとメールーサーバを検証する仕組みですが、DKIMはEnvelope Fromに失敗したときはFrom（送信元）でも検証します。その仕組みは電子署名を使います、メール本文からメールヘッダーまでを使い秘密鍵で電子署名をしてメール送信します、受信メールサーバはあらかじめ公開された公開鍵を使って送信されたメールを検証します。

===[column] DomainKeysとIIMの違い

メールに対して電子署名をする仕組みはDomainKeysとIIM(Identified Internet Mail)が存在していた、DKIMはこの2つの仕組みの長所を掛け合わせたものです。

DomainKeysもIIMもメールに秘密鍵で電子署名してメール送信しますが、IIMは公開鍵もメールで送るオプションがありDKIMはそれを行っておりません、それとDomainKeysでは認証単位がドメイン名（FQDN）で、DKIMはメールアドレス単位での認証に変更されています。

===[/column]



=== 正当性の確認プロセス

//image[dkim][DKIMの確認プロセス][scale=0.7]

 1. 送信元がメールを送信する。
 2. 受信メールサーバにリクエストがくる。
 3. 受信内容からEnvelope Fromを取得しドメイン名を取り出す。
 4. 受信内容からDKIM-Signatureのヘッダーを取り出す。
 5. 取り出したドメイン名にサブドメイン名を付加したホスト名@<fn>{_domainkey}のTXTレコードからDKIM情報を取り出す。
 6. 取り出したDKIM情報を使ってDKIM-Signatureの内容を復号化する。
 7. 復号化してDKIM-Signatureのhパラメーターに記載されているヘッダー情報と比較してすべて一致したら認証成功とする。

hパラメーターについては@<hd>{送信されるときのヘッダー}で述べる。

//footnote[_domainkey][ホスト名の形式は セレクタ名._domainkey.ドメイン名(FQDN). になっています、セレクタ名は使うメールサーバの設定に従ってください。]


== 設定説明
DKIMの設定説明をします。

//list[一般的な例][bash]{
v=DKIM1; k=rsa; p=<公開鍵>
//}
SPFレコードの違って、設定の区切りはスペースではなく@<code>{;}です、@<code>{Parameter=Value;}が設定の基本です。

//table[DKIM][パラメータの説明]{
Parameter	Value	意味
------------------------------------------------------------
v	DKIM1	DKIMの識別子とバージョン番号、バージョン番号は1のみです。
k	rsa	電子署名の生成の際に利用できる鍵の形式を指定です。@<br>{}DKIMではRSA形式しかサポートしていません、省略できます。
p	<公開鍵>	公開鍵を設定します。@<br>{}あらかじめ送信メールサーバにおいて生成した公開鍵を設定します。
//}

== 送信されるときのヘッダー
//list[送信されるときに追記されるヘッダー情報][bash]{
v=1; a=rsa-sha256; c=relaxed/relaxed;
d=exsample.com; s=20150623;
h=mime-version:references:in-reply-to:from:date:message-id:subject:to;
bh=<本文のハッシュ値>;
//}
メール送信するとき電子署名だけじゃなく、さまざまな情報が付加されます、設定には関係ないですが検証時に使う情報がここには含まれています、hパラメーターがそれです。@<b>{hパラメーターに含まれるヘッダーを検証すると同時にメールをリレーするメールサーバは検証を妨害しないように、これらのヘッダーを変更したり修飾しないようにします}。

@<list>{送信されるときに追記されるヘッダー情報}の例では@<code>{:}で区切った8つのメールヘッダーを検証に使用します。


== 判定結果
受信サーバは @<code>{Authentication-Results}というヘッダーに@<code>{dkim=}の形式でDKIMレコードの検証結果を記録します、記載された情報は次の表です。

//table[Authentication-Results][Authentication-ResultsのDKIM検証結果]{
判定	意味
------------------------------------------------------------
pass	電子署名の認証に成功した。
hardfail	電子署名の認証に失敗した。
neutral	送信元の公開鍵を用意していない。
none	送元がDKIM情報を用意していない。
permerror	送信元のドメインに一時的なトラブルが発生している。
//}

hardfail判定されたメールは迷惑メールと判定しても良いと思います。

2019年現在、DKIMに対応したメールサーバは多くなく@<code>{Authentication-Results}ヘッダーに@<code>{dkim=}の記載されていることが少ないです。DKIMの判定がないとしても迷惑メールと判定しないほうが良いと思います。

== DKIMにて得られる効果
DKIMは迷惑メールを防止する仕組みで使われていますが、電子署名の機能も持っているのでメールの改ざん防止の役割も兼ねています、検知する機能はないのですが、メールの安全性からもDKIMの設定を推奨します。

== DKIM未対応のメールサーバについて
@<b>{SPFは対応しているが、DKIM未対応のメールサーバはあります。}

これは、SPF対応は受信側メールサーバだけで済むのですが、受信側だけではなく送信側メールサーバの対応も必要になるためです。送信側メールサーバ（もしくは関連サーバ）は公開鍵暗号方式に基づいた@<b>{秘密鍵・公開鍵を動的に生成して}、動的生成した公開鍵をDNSサーバに設定するため利用者に対して公開して、動的に生成した秘密鍵を使用してメールへの電子署名をする。このように@<b>{DKIMをサービスとして運用するのは少々大変です}。

国内のメールサーバはSPFに対応しているところが多いですが、DKIMに対応しているところは少ない感じです、2019年の時点ではSPF対応をしていればGmailをはじめとするメールサービスは？表示はしませんし迷惑メールの判定はしないです。


しかし、この基準は将来も守られることはないです、DKIM対応メールサーバが増えればSPFとDKIM両方対応じゃないと迷惑メールと判定する時代になるかもしれません。そうなったとき慌てる前にDKIM対応のメールサーバに移行することを推奨します。
