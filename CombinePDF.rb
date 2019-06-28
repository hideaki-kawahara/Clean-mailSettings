require "combine_pdf"
pdf = CombinePDF.new
pdf << CombinePDF.load("cover.pdf")
pdf << CombinePDF.load("Clean-mailSettings.pdf")
pdf.save "Clean-mailSettings2.pdf"
