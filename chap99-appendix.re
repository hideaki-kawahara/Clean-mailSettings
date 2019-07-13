= Appendix
== 各種確認ツール
SPFレコードやDKIMレコードが正しく設定されているの確認ができます。MX TOOLBOSが使いやすいので紹介します。

=== SPF確認ツール
URL:@<href>{https://mxtoolbox.com/spf.aspx}

//image[spf1][SPF確認ツール][scale=0.5]
Domain Nameの欄にドメイン名を入力して、SPF Record Lookupを押下します。

//image[spf2][SPF確認結果][scale=0.3]
正しい設定ならばSPFレコードの設定が表示されます。

=== DKIM確認ツール
URL:@<href>{https://mxtoolbox.com/dkim.aspx}

//image[dkim1][DKIM確認ツール][scale=0.5]
Domain Nameの欄にドメイン名を入力して、Selectorにセレクター名を入れます、@<b>{_domainkeyの入力は不要です}、そしてDKIM Lookupを押下します。

//image[dkim2][DKIM確認結果][scale=0.3]
正しい設定ならばDKIMレコードの設定が表示されます。

=== その他確認ツール
URL:@<href>{https://mxtoolbox.com/NetworkTools.aspx}

特にblacklistなどは使用しているドメインが迷惑メール判定されメールが一切届かなくなった確認に便利です、ドメインごと迷惑メール判定されるとエラーメールにならず届かないという現象になるので、このような確認ツールを使うのが良いです。


//raw[|latex|\pagebreak]
== DNSサーバに慣れてみよう
DNSサーバを使った遊びです。TXTレコードは原則ルールはありません、ホスト名にプリフィックス名を付けているならほぼ自由に遊びができます。今回使用したドメイン名にも、そんな遊びをやっております、以下にコマンドを紹介するので、ご確認ください。

//emlist[Twitter][bash]{
$ dig -t txt _twitter.bright-system.dev | grep Twitter
//}
//emlist[Facebook][bash]{
$ dig -t txt _facebook.bright-system.dev | grep Facebook
//}
//emlist[Blog][bash]{
$ dig -t txt _blog.bright-system.dev | grep Blog
//}
//emlist[Qiita][bash]{
$ dig -t txt _qiita.bright-system.dev | grep Qiita
//}
