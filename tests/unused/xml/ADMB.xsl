<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- $Id: ADMB.xsl 2944 2012-02-07 01:18:24Z jsibert $ -->
<xsl:template match="/">
  <html>
  <body>
  <h1>ADMB parameter file: <xsl:value-of select="FIT/@id"/> </h1>

  <h2>Fit Statistics</h2>
  <table border="1">
  <xsl:for-each select="FIT/*[@category='STAT']">
    <tr>
       <td>Number of Parameters</td>
       <td align="right"><xsl:value-of select="n"/></td>
    </tr>
    <tr>
       <td>Likelihood Value</td>
       <td align="right"><xsl:value-of select="value"/></td>
    </tr>
    <tr>
       <td>Likelihood Value Without Penalty</td>
       <td align="right"><xsl:value-of select="fun_without_pen"/></td>
    </tr>
    <tr>
       <td>Maximum Gradient Contribution</td>
       <td align="right"><xsl:value-of select="gmax"/></td>
    </tr>
  </xsl:for-each>
  </table>
       


  <h2>ADMB Model Parameters</h2>
  <table border="1" width="75%">
    <tr bgcolor="#9acd32">
      <th>Parameter Title</th>
      <th>.tpl Variable Name</th>
      <th>Value</th>
      <th>Bounds</th>
      <th>Phase</th>
      <th>Active</th>
    </tr>
  <xsl:for-each select="FIT/*[@category='VAR']">
  <tr>
      <td><xsl:value-of select="title"/></td>
      <td><xsl:value-of select="local-name()"/></td>
      <td><xsl:value-of select="value"/></td>
      <td><xsl:value-of select="bounds/min"/> to 
          <xsl:value-of select="bounds/max"/></td>
      <xsl:choose>
         <xsl:when test="phase &gt; 0">
           <td align="center">
           <font color="#ff0000">
           <xsl:value-of select="phase"/>
           </font></td>
         </xsl:when>
         <xsl:otherwise>
           <td align="center"><xsl:value-of select="phase"/></td>
         </xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="active &gt; 0">
           <td align="center">
           <font color="#ff0000">
           <xsl:value-of select="active"/>
           </font></td>
         </xsl:when>
         <xsl:otherwise>
           <td align="center"><xsl:value-of select="active"/></td>
         </xsl:otherwise>
      </xsl:choose>
   </tr>
  </xsl:for-each>
  </table>

  <h2>ADMB Model Data</h2>
  <table border="1" width="75%">
    <tr bgcolor="#9acd32">
      <th>Data&#160;Element</th>
      <th>Variable&#160;Name</th>
      <th>Value</th>
    </tr>
  <xsl:for-each select="FIT/*[@category='CON']">
  <tr>
      <td><xsl:value-of select="title"/></td>
      <td><xsl:value-of select="local-name()"/></td>
      <td><xsl:value-of select="value"/></td>
   </tr>
  </xsl:for-each>
  </table>


  </body>
  </html>
</xsl:template>

</xsl:stylesheet> 
