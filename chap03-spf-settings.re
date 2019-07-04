= SPF
SPF(Sender Policy Framework)の説明をします。SPFは送信ドメイン詐称を防いで正当なドメイン名から送信していることを検証する仕組みです。

== SPFの説明
メールの基本的構造でも記載しましたが、From(送信元)とEnvelope Fromとメールーサーバーのドメイン名が異なっていてもメール送信できます、実在しないメールアドレスからでも送れます。ここで問題なのはメールサーバーのドメイン名から関係ないメールアドレスとしてがFrom(送信元)から迷惑メールとして送信されることです、From(送信元)は仕様上では封筒の中身であり、メールサーバーがチェックしてメール配信を拒否することは盛り込まれておりません。そのため受信側で迷惑メールであると判定する仕組みが考えれました、これがSPFです。

=== 正当性の確認プロセス

ここに図が入る

IPアドレスは詐称が難しいので、受信側のメールサーバーはFrom(送信元)の記載されたドメイン名からDNSサーバーのTXTフィールドのSPFレコードを取得し、そこに記載されいるIPアドレスと、送信元のメールサーバーのIPアドレスを比較してFrom(送信元)が正当な送信元メールサーバーであることを確認します。




=== SPFレコードの書き方
@<code>{バージョン　空白　定義　空白　定義} と続きます。
定義はディレクティブ（directive）と修飾子（modifier）で構成する場合と、限定子（qualifier）と機構（mechanisms）で構成する場合があります。ディレクティブ（directive）と修飾子（modifier）の場合はお互いを接続する記号は@<code>{:}です。

@<code>{v=spf1 include:_spf.google.com ~all}


=== SPFのステータス

== SPFで得られる効果
