<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
 <html>
  <head/>
  <body>

   		<ol style="list-style:decimal outside">
   		<xsl:for-each select="Order">
   			<li><b>Orderkey : </b> <xsl:value-of select="@key"/><br/>
 	
   				<xsl:for-each select="Customer">
   					<b>Customer</b><br/>
     				<xsl:for-each select="Name | Email">
						<xsl:value-of select="name()"/><xsl:text> : </xsl:text><xsl:value-of select="."/>
						<xsl:text>, </xsl:text>
     				</xsl:for-each>
   				</xsl:for-each>   

				<br/><br/>
				<ol type="A">
    				<xsl:for-each select="Part">
    					<li><b>Parts</b><br/>
						Color : <xsl:value-of select="@color"/><xsl:text>, </xsl:text>
						
     	 				<xsl:for-each select="key | Quantity | ExtendedPrice | Tax">
							<xsl:value-of select="name()"/><xsl:text> : </xsl:text><xsl:value-of select="."/>
							<xsl:text>, </xsl:text>
						</xsl:for-each>

						<br/><br/>
						<ol type="a">
     	 				<xsl:for-each select="Shipment">
     	 					<li><b>Shipment</b><br/>
      						<xsl:for-each select="ShipDate | ShipMode">
								<xsl:value-of select="name()"/><xsl:text> : </xsl:text><xsl:value-of select="."/>
								<xsl:text>, </xsl:text>
     						</xsl:for-each>
     						</li>
     	 				</xsl:for-each>
     	 				</ol>	
     	 				<br/>
     	 			</li>
    				</xsl:for-each>
    	 			</ol>
   			</li>
  		</xsl:for-each>
   		</ol>

  </body>
 </html>
</xsl:template>
</xsl:stylesheet>