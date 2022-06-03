1000 constant dict-size
dict-size reserve constant dict-start

dict-size dict-start task constant t

t{ t ttop @ -> dict-start dict-size + cell - }t