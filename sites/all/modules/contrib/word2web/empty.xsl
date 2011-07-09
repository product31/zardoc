<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:v="urn:schemas-microsoft-com:vml"
  xmlns:o="urn:schemas-microsoft-com:office:office"
  xmlns:w="urn:schemas-microsoft-com:office:word"
  xmlns:st1="urn:schemas-microsoft-com:office:smarttags"
  exclude-result-prefixes="v">

<xsl:output method="html"
  omit-xml-declaration="yes"
  encoding="UTF-8"
  indent="yes" />

<xsl:template match='/'>	
  <xsl:apply-templates select="*" />
</xsl:template>

<!-- This is a fairly broad match where we clean up as many elements as possible -->
<xsl:template match="*">
  <xsl:if test="normalize-space(.)">
    <xsl:element name="{name()}">
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates/>
    </xsl:element>
  </xsl:if>
</xsl:template>

<!-- Overide the * match for spans so we don't destroy inline spacing -->
<xsl:template match="span">
  <!-- this doesn't actually do much except drop spans formating -->
  <xsl:if test="normalize-space()">
    <!-- Continue applying templates. There could be formating inside our spans. -->
    <xsl:apply-templates/>
  </xsl:if>
</xsl:template>

<!--
<xsl:template match="img" priority="-1">
  <xsl:element name="{name()}">
    <xsl:apply-templates select="@*"/>
    <xsl:apply-templates/>
  </xsl:element>
</xsl:template>
-->

<xsl:template match="@*">
  <xsl:if test="normalize-space(.)">
    <xsl:attribute name="{name(.)}">
      <xsl:value-of select="."/>
    </xsl:attribute>
  </xsl:if>
</xsl:template>

</xsl:stylesheet>
