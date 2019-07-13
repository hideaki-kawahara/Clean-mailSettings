= Appendix
== さくらのメールボックスについて
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
