import Ravl
img = Ravl.ImageByteRGBValueC(50,100)
img.Fill(Ravl.ByteRGBValueC(255,0,0))
Ravl.Save("@X",img)
