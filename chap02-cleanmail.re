= きれいなメールとは？
この本での「@<b>{きれいなメール}」の定義をします、メールの文面の話ではありません。
== きれいの定義

 * 送信元メールアドレスが正しい形式であるか？
 * きちんとした場所から送信しているか？
 * 認証されたメールサーバーを使っているか？
 * メールサーバー同士の通信は暗号化されているか？

上の4つのことが守れているメールは「きれいなメール」と呼びます、1つでも守られていなければメールは迷惑メールとして判定され、メールを送信しても届かないことになることも考えられる、これらの状況を確認して「きれいなメール」になるために再点検しましょう！
== 送信元メールアドレスにおける「きれい」
多くのメールサーバーにおいて送信元のメールアドレスにドメイン名を使用しないと送信拒否の設定になっている、そしてメールアドレスに使用するドメイン名をはFQDN@<fn>{FQDN}形式でなければならないです、IPアドレス@<fn>{IPアドレス}形式のメールアドレスを許可しているメールサーバーも存在しますが、仮に送信できたとしても受信側のメールサーバーでエラーとして判定することも考えられます、受信サーバーまで到達してもGmailをはじめとする多くのメールサーバーで採用されている@<b>{迷惑メールフィルターが迷惑メールとして判定}します、迷惑メールフィルターにおいてIPアドレス形式のメールアドレスは迷惑メールとして判定します。@<br>{}

IPアドレス形式なんかしてないと思っていても、ドメイン名の設定にミスがあるとメール送信ができませんし送信先に届きません、例えば@<code>{mail.sample.com}のmailのホスト設定にミスがあると、FQDN形式ではないと判定されるので注意が必要です。@<br>{}
この辺りはDNS周りの知識が必要です、DNSの知識は避けて通ることはできません、この機会にDNSの知識を習得してください、今はDNSの設定はWebで完結しますので気軽にDNS設定を修正して体験することをお勧めします。

===[column] IPアドレス形式のメールアドレス
今は使うことが無いですが、コラムとしてIPアドレス形式のメールアドレスの書き方を記載します。

@<code>{hoge@192.168.0.1}という形ではエラーになります。正しくは@<code>{hoge@[192.168.0.1]}という形式で書きます。

===[/column]

//footnote[FQDN][Fully Qualified Domain Nameのことで日本語では「完全修飾ドメイン名」と呼ばれる、FQDNで指定されたホストはインターネット上で特定できることになっている。]
//footnote[IPアドレス][ネットワーク上の住所と呼ばれている、機器を識別するために割り当てられているもの、グローバルなネットワークつまりインターネットでは一定のルールに従い割り当てが行われている。]

== 送信元の正しい場所における「きれい」
メールを送信する場所、インターネットにおける場所は重要な要素です、たとえば仕事をする上で情報にアクセスするときに制限を加えることがありますが、そのときに使用するのがIPアドレス制限であり正しいところからアクセスしているのかを確認しています、メール送信でも同じでメールアドレス所有者が正しいところからアクセスしているのかが重要になります。

今でこそ、メールはメールアドレスを預かっているメールサーバーから送信するのが当たり前ですが、2005年ぐらいまでは郵便と同じようにメール送信はどこからでも可能でした。しかし迷惑メールの標的となりメール送信に対して制限がかかるようになりました。

===[column] メール送信制限の歴史

メール送信制限は迷惑メールとの戦い歴史でした、次のあげるテクノロジーが導入されていきました。

 1. Outbound Port25 Blocking(25番ポートブロック)
 2. POP before SMTP
 3. SMTP Authentication(サブミッション 587番ポート)

　今現在のメール送信プロトコルは2種類あります、当初は1つしかなく最初にあったメール送信のプロトコルは認証に対応していませんので、そのためこのプロトコルは使われないようになりました。Outbound Port25 Blockingにより認証の無いメール送信はブロックするようになりました。

　そのため、新しいメール送信方法が考案されました、POP before SMTPとSMTP Authenticationです、POP before SMTPはメール受信が認証があることを利用しており、メール受信をしたら対象のIPアドレスから一定時間メール送信を許可します。こちらはメールサーバー自体の変更をしなくても実現可能な方法ですが、仕組み自体がシンプルでないのと、メール受信さえしてしまえば良くて送信については結局何も考慮されていないということで次第に廃れていきました。
　SMTP Authenticationはメール送信のプロトコルに対して認証ルールを追加しています、認証を追加するにあたり既存のプロトコルを拡張するのではなく新たなプロトコルを追加しました、これがサブミッション 587版ポートになります。現在はSMTP Authenticationの方が使うのが一般的です。

===[/column]

現在のメールサーバーは、WebメールやSMTP Authenticationを使うことが多く、ログインまたはメール送信認証さえ通れば送信元が正しいとなります、しかし、この情報を受信するメールサーバーは知ることができません。@<b>{受信側のメールサーバーが送信元の正しい場所を判定する仕組みがSPFです}。

== メールサーバーにおける「きれい」



== メールサーバーリレーにおける「きれい」
