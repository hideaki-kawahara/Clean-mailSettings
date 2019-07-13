= メールの基本的構造

メールに関する設定を行う前にメールの基本的な構造を学ぶことより一層の理解ができます。

== メールは封筒です
//image[envelope][メールの構造][scale=0.5]

Webメールの画面やメールソフトで見ているとき郵便物で例えると封筒を開封した状態で見ています、件名一覧のときも出てくる情報も開封した中身を見ています、普段の使い方では封筒の外側を見ることはないのです。メールソフトで見ているFrom(送信元)とTo(送信先)は封筒の中に書かれている内容です。


封筒の外のことはメールヘッダ@<fn>{メールヘッダ}に記載されています、メールヘッダを見ることは普段はしないですが重要な情報が書かれています、メールを出された場所や経由してきたところなどが書かれています、メールを返信するとスレッド状になって見ることができるのもメールヘッダに記載された情報を元に実現している機能です。@<b>{SPFやSender IDやDKIMもメールヘッダに記載されいる}ので見たことない人は一度見ることを推奨します。

== Envelope To
ここで一つ疑問が出てきます、メールソフトで見ているTo(送信先)が、封筒の外に書かれている内容は異なっても送ることができるのか？ということです、実際のところTo(送信先)と異なっても送信できます、メールを送信する先は封筒の外に書かれている内容を元にしているのでTo(送信先)は飾りでもフェイクであっても問題ないのです、To(送信先)に大量のメールが列挙されていることがありますが、こちらも同じように、これがそのままの状態で封筒の外に書かれているわけではありません、@<b>{メールサーバがTo(送信先)の数だけ封筒を作ってからメールを送信しています}、封筒はメールサーバが作っているのです、このときの封筒の送信先をEnvelope ToとかRCPT TOということがありますが、RCPT TOはメールサーバへのコマンドです、@<img>{envelope}にもメールコマンドとして記載しておりますが、この本ではEnvelope Toに統一します。


それから最近は見かけることが減りましたが、Bcc(ブラインドカーボンコピー)というのがあります、これも同じでメールサーバが封筒を作ってから送信先をBcc(ブラインドカーボンコピー)から取得します、送信先に自分が書かれていなくても届くのは、この仕組みを使っているからです。

//footnote[メールヘッダ][メールヘッダとは、メールの送信情報が書かれています、Gmailは右端のその他から「メッセージのソースを表示」から見ることができます(Gmailアプリからは見ることができません)]

== Envelope From
Envelope ToがあればEnvelope Fromも当然存在ます、意識していなければメールアドレスはFrom(送信元)とEnvelope Fromを同じにしますが、メルマガなど大量メール配信の場合などはプログラムで処理をするなどで異なるメールにすることがあります、@<b>{Envelope Fromをメール送信を失敗したときにメールサーバが返信するため送信先メールアドレスとして設定する}ことをします。よく見かける「@<b>{これは送信専用メールです}」とメール本文に書かれているメールはFrom(送信元)とEnvelope Fromを異なるメールアドレスに設定しているのです、このメールに対して返信をするとFrom(送信元)とは異なるメールが表示されることがあると思います、返信したときに表示される送信先メールアドレスがEnvelope Fromです。@<img>{envelope}にMAIL FROMと記載しているが、この本ではEnvelope Fromに統一します。


そしてFrom(送信元)とEnvelope Fromが実際に存在していなくてもメールは届きます、これはメールの仕組み上メールを送ることが主目的に作られているためです、これを@<b>{悪用したのが迷惑メールでありフィッシングメール}です。
