= まえがき

//image[gmail][Gmailに出てくる？マーク]
Gmailにて、このようなメールが届いたことありますか？@<br>{}
または、試しに会社や取得したドメインからメールをGmailアドレスメール送信してみてください。@<br>{}
Gmailで表示される？マークはスパムメールとして判定される前段階の状態、このまま放置しておくとスパムメールとしてメールが届かなくなります。この状態にならないため早めの対策が必要です。@<br>{}
メールの仕組みと歴史的な経緯もありメールを送信した場所（ドメイン）とメールサーバの正当性を担保することはメールサーバだけでは不可能です。これらの技術はSPF@<fn>{SPF}とDKIM@<fn>{DKIM}によって行われます。


本書は、メールの基本的な構造とメール送信で必要不可欠なSPFやDKIMの話を、わかりやすく解説した本です。この本を読めばメールのことを深く知り、そしてSPFやDKIMの基礎的なことが身につき送信するメールがスパムメールにされなくなります。

今後も使われるメールを長く付き合うためにも本書を読んでいただけたら幸いです。

//footnote[SPF][SPF(Sender Policy Framework)とは、送信ドメイン詐称を防いで正当なドメインから送信を検証する仕組み]
//footnote[DKIM][DKIM(Domainkeys Identified Mail)とは、送信ドメインを電子署名で認証する仕組み]


===== 本書で得られること

 * メールの基本的な構造の知識
 * メール送信の正当性についての知識
 * SPFについての基礎的な知識
 * DKIMについての基礎的な知識
 * スパムメールにならないための設定知識


===== 対象読者

 * 会社のメールアドレスからメールを出しても、クライアントから届かないと言われて困っている人
 * フリーランスで仕事をはじめたけど、独自ドメイン送信したメールがクライアントに届くか心配な人
 * ドメインを取得したけど、メールを使っていない人


===== 前提知識

 * メールの知識
 * ドメイン取得する知識
 * ドメイン設定を変更できるだけの知識
 * DNSに関する簡単な知識

===== メールについて

 * メールの表記について電子メールやeメールと表記することがありますが、この本では「メール」に統一してます、同様に「メールアドレス」に統一してます。

===== 問い合わせ先

 * URL: https://sapi-kawahara.netlify.com/
 * Twitter: @sapi_kawahara
