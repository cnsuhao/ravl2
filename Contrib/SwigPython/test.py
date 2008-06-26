import Ravl
img = Ravl.ByteRGBImageC(100,100)
img.Fill(Ravl.ByteRGBValueC(255,0,0))
Ravl.Save("@X",img)
