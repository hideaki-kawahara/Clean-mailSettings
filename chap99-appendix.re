= Appendix
== 各種確認ツール
SPFレコードやDKIMレコードが正しく確認できているかを確認する方法を紹介します。確認するために使えるツールやサービスはいろいろありますが、ここでは比較的使いやすいMXTOOLBOXを紹介します。

=== SPF確認ツール
URL:@<href>{https://mxtoolbox.com/spf.aspx}

//image[spf1][SPF確認ツール][scale=0.5,pos=H,border=on]
Domain Nameの欄にドメイン名を入力して、SPF Record Lookupを押下します。

//image[spf2][SPF確認結果][scale=0.2,pos=H,border=on]
正しい設定ならばSPFレコードの設定が表示されます。

=== DKIM確認ツール
URL:@<href>{https://mxtoolbox.com/dkim.aspx}

//image[dkim1][DKIM確認ツール][scale=0.45,pos=H,border=on]
Domain Nameの欄にドメイン名を入力して、Selectorにセレクター名を入れます、@<b>{_domainkeyの入力は必要ないです}、そしてDKIM Lookupを押下します。

//image[dkim2][DKIM確認結果][scale=0.2,pos=H,border=on]
正しい設定ならばDKIMレコードの設定が表示されます。

=== その他確認ツール
URL:@<href>{https://mxtoolbox.com/NetworkTools.aspx}

とくにblacklistなどは使用しているドメインにおいて迷惑メール判定されメールが一切届かなくなった場合の確認に便利です。ドメインごと迷惑メール判定されるとエラーメールにならず届かないという現象になるので、このような確認ツールを使うのが良いです。

