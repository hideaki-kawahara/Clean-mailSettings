= きれいなメールとは？
この本での「@<b>{きれいなメール}」の定義をします、メールの文面の話ではありません。

== きれいの定義

 * 送信元メールアドレスが正しい形式であるか？
 * きちんとした場所から送信しているか？
 * 認証されたメールサーバを使っているか？
 * メール通信は暗号化されているか？

上の4つのことが守れているメールは「きれいなメール」と呼びます、ひとつでも違反していると、きれいなメールとは判定されません。きれいなメールでないと、場合によってはメールは迷惑メールとして判定され、メールを送信しても届かないことになることも考えられる、これらの状況を確認して「きれいなメール」になるため再点検しましょう！


== 送信元メールアドレスにおける「きれい」
多くのメールサーバにおいて送信元のメールアドレスにドメイン名を使用しないと送信拒否の設定になっている、そしてメールアドレスに使用するドメイン名はFQDN@<fn>{FQDN}形式でなければならないです。IPアドレス@<fn>{IPアドレス}形式のメールアドレスを許可しているメールサーバも存在しますが、仮に送信できたとしても受信側のメールサーバでエラーとして判定することも考えられます。受信サーバまで到達してもGmailをはじめとする多くのメールサーバで採用されている@<b>{迷惑メールフィルターが迷惑メールとして判定}します、迷惑メールフィルターにおいてIPアドレス形式のメールアドレスは迷惑メールとして判定します。@<br>{}

IPアドレス形式なんかしていないと思っていても、ドメイン名の設定にミスがあるとメール送信ができませんし送信先に届きません、たとえば@<code>{mail.sample.com}のmailの場合、ホスト側に設定ミスがあると、FQDN形式ではないと判定されるので注意が必要です。@<br>{}
この辺りはDNS@<fn>{DNS}およびDNSサーバ周りの知識が必要です、DNSの知識は避けて通ることはできません、この機会にDNSの知識を少しでも習得することを推奨します、今はDNSの設定はWebで完結しますので気軽にDNS設定をいじって体験することを推奨します。

===[column] メールアドレスはFQDNである必要性
@<b>{サーバのホスト名は勝手に名乗れます！！}

メールのシステム自体がローカルネットワークでも使用する仕組みをそのままインターネット用に拡張したため、その当時の仕様がそのまま残っています、そのため@<b>{メールサーバのホスト名は勝手に名乗れます}、実際にメールを送信する側は好き勝手なメールサーバ名を名乗り送信できるので、これが迷惑メールの根本的な原因です。メールアドレスがFQDNであることは非常に重要な要素です。

そしてメールを受信する側は届くことを考慮して、インターネットでドメイン名に紐づいたメールサーバをDNSサーバに記載します、FQDNであれば確実に届きます。

===[/column]

===[column] IPアドレス形式のメールアドレス
今は使うことがないですが、コラムとしてIPアドレス形式のメールアドレスの書き方を記載します。

@<code>{sample@192.168.0.1}という形ではエラーです。

正しくは@<code>{sample@[192.168.0.1]}という形式で書きます。

===[/column]

//footnote[FQDN][Fully Qualified Domain Nameのことで日本語では「完全修飾ドメイン名」と呼ばれる、FQDN指定されたホストはインターネット上で特定できることになっている。]
//footnote[IPアドレス][IPアドレスはネットワーク上の住所と呼ばれている、機器を識別するために割り当てられているもの、グローバルなネットワークつまりインターネットでは一定のルールに従い割り当てが行われている。]
//footnote[DNS][Domain Name Systemのことでドメイン名とIPアドレスを紐づけるシステムです。]


== 送信元における「きれい」
メールを送信する場所、インターネットにおける場所は重要な要素です、たとえば仕事をする上で情報にアクセスするとき制限を加えることがありますが、そのときに使用するのがIPアドレス制限であり正しいところからアクセスしているのかを確認しています、メール送信でも同じでメールアドレス所有者が正しいところからアクセスしているのかが重要です。

今でこそ、メールはメールアドレスを預かっているメールサーバから送信するのが当たり前ですが、2005年ぐらいまでは郵便と同じようにメール送信はどこからでも可能でした。しかし迷惑メールの標的となりメール送信に対して制限がかかるようになりました。メールサーバが管理しているドメイン名とEnvelope Fromが一致しないと送信できなくなりました。

現在のメールサーバは、Webメールだったり送信時に認証を加えることで送信元の正当性の検証を行っております、ログインまたはメール送信認証さえ通れば送信元が正しいと判断されます。

===[column] メール送信制限の歴史

メール送信制限は迷惑メールとの戦い歴史でした、次のあげるテクノロジーが導入されていきました。

 1. Outbound Port25 Blocking（25番ポートブロック）
 2. POP before SMTP
 3. SMTP Authentication（サブミッション587番ポート）

現在のメール送信プロトコルのSMTP@<fn>{SMTP}は2種類あります、最初に考案されたメール送信のプロトコルは認証に対応していません、そのため現在は使われないようになりました。Outbound Port25 Blockingにより認証のないメール送信はポート番号@<fn>{ポート番号}からブロックするようになりました。なお25番というのは最初に使われたメールのポート番号です。


そして新しいメール送信方法が考案されました、POP before SMTPとSMTP Authenticationです、POP before SMTPはメール受信することであるPOP@<fn>{POP}が認証することを利用しており、メール受信をしたら対象のIPアドレスから一定時間メール送信を許可します。こちらはメールサーバ自体の変更をしなくても可能な方法ですが、仕組みがPOPに頼ることでPOPサーバの負荷がムダにあがってしまうのと、メール受信さえしてしまえば良くて送信については結局何も考慮されていないということでしだいに廃れていきました。


SMTP Authenticationはメール送信のプロトコルに対して認証ルールを追加しています、許可されたユーザーのみに対して送信をするように認証する仕組みを追加しています。認証を追加するにあたり既存のプロトコルを拡張するのではなく新たなプロトコルを追加しました、これがサブミッション587番ポートです。現在はSMTP Authenticationを使うのが一般的です。


===[/column]


//footnote[SMTP][Simple Mail Transfer Protocolのこと、メールには、送信、配信、転送、受信など多数の機能があるが、それらを意識せずにSMTPを使うだけで済ませることができる。]
//footnote[ポート番号][ポート番号は部屋の番号で、IPアドレスを住所とすると例えると理解しやすいです、IPアドレスとポート番号を目指して通信します。]
//footnote[POP][Post Office Protocolのこと、メールサーバからメールをダウンロードし、メールはサーバから削除する、郵便と同じ仕組みの受信方法です。]



== メールサーバにおける「きれい」
メールサーバは他のメールサーバと通信しています、メールサーバは近くのメールサーバへリレーをすることでメールを届けています、いくつものメールサーバを経由してメールが届いているのです。ここに認証を入れることが事実上不可能となっております、ここでは認証のない世界が現在もあります。

そのような状況で迷惑メールを送信する人たちは考えました、送信するためのメールサーバが使えないのであれば、メールサーバを立てれば良いのです、そうメールサーバリレーに紛れてしまえば良いと考えました。一応ですがメールサーバのリレーはIPアドレスによる制限はかけていますので多少の防御できます、しかしメールサーバの数が爆発的に増えている状況の中においてIPアドレスによる制限には限界があります。

ここで考えることはメールサーバのアクセス制限ではなく、メールサーバが正しいということがリレー間で担保されれば良いことです、
それが@<b>{SPF}、@<b>{sender ID}、@<b>{DKIM}です。


== メール通信内容における「きれい」
メールサーバ間での通信は歴史が長くUUCP@<fn>{UUCP}時代までさかのぼります、その頃のインターネットは性善説による世界でありました、このような世界ではすべての通信プロトコルは暗号化通信を行っていません。多くの人がインターネットを使うようになってから性善説が通用しなくなりました、現在は多くのプロトコロルが暗号化通信をするようになりました、メールに関しても暗号化通信が導入されていきました。SMTPは暗号化通信しておりません、メール本文がそのまま暗号化せずにインターネットを流れ行きます、POPに至ってメール本文だけじゃなくログインIDとパスワードを平文で流してしまいます、とても危険です。


メールの暗号化には2種類の方法が使用されています。TLS@<fn>{TLS}とSTARTTLS@<fn>{STARTTLS}です。
TLSはWebの世界で一般的な方法です、SSLということもありますが、この本ではTLSに統一します、TLSを使ったメール送信ではプロトコル自体が異なってしまうので今まで使っていたポートは使えませんので新しいポート番号を設定します。送信ではSMTP over TLSを使用し、受信も同様に新しいポート番号を設定しPOP over TLSまたはIMAP@<fn>{IMAP} over TLSを使って受信をします。アプリケーションの自動設定やWebメールの利用で、利用者の方で多く使われております。

もう1つのSTARTTLSは、非暗号化通信の途中で暗号化通信に変更が可能なやり方でメールの通信などをを行います、このため既存のポート番号を変更しなくても良いというメリットがあります。さらに接続先のメールサーバが暗号化に対応していない場合は暗号化モードに入らず非暗号化のまま通信します、接続してきたメールサーバが非暗号化のまま通信してきたら続行すれば良いなど多くのメリットがあるためメールサーバのリレーでよく使われています、Gmailが使用したため多くのメールサーバで採用されています。

STARTTLSに対応させるにはメールサーバの再インストールが必要になるケースもあり、物凄く手間です。そのため今回この本では書きません、@<b>{STARTTLSに未対応のメールサーバだったら対応サーバに移転を推奨します}。

//image[gmail][To自分の前に出る鍵が開いたアイコン]

ご使用のメールをGmail宛にメールして鍵が開いたアイコン表示だったら、STARTTLS非対応と思って間違いないです。

===[column] APOPについて
メールの暗号化についてAPOP(Authenticated Post Office Protocol)を出さなかったのは、使うべきではないプロトコルであるからです。

APOPはログインIDとパスワードの暗号化にMD5を使用しています。

MD5は暗号学的ハッシュ関数と呼ばれ物の一種です。暗号学的ハッシュ関数は入力された値から規則に基づいた入力された値とは異なる固定長文字列の値を出力する仕組みです、利点としては出力する値の計算が早く、出力された値から簡単に入力された値が簡単推測できない仕組みです。

しかしMD5は2004年8月、衝突耐性に問題有りと提言され、2007年にはIPAよりAPOPを使用しない注意喚起が出された、これによりMD5を使ったメール暗号化は使用してはいけない方式となりました。



脆弱性関連情報取扱い：APOP方式におけるセキュリティ上の弱点（脆弱性）の注意喚起について @<href>{https://www.ipa.go.jp/security/vuln/200704_APOP.html}

===[/column]




//footnote[UUCP][Unix to Unix Copy Protocolのこと、初期のインターネットで使われたプロトコル、1日1回まとめて通信するなどの機能がある。]
//footnote[TLS][Transport Layer Securityのこと、セキュリティ通信を行うためのプロトコルです。アプリケーションに対して中立な実装なので、他のプロトコルに追加できる仕組みになっている。]
//footnote[STARTTLS][STARTTLSはメールの送受信するプロセスにおいて暗号化通信する仕組みです。]
//footnote[IMAP][Internet Message Access Protocolのこと、POPと異なり、メールをメールサーバ上に保存したまま管理する。Webメールはこの仕組みを使っている。]
