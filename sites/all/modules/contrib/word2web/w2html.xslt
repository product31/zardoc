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

<xsl:strip-space elements="v:* o:* w:* st1:* p"/>

<xsl:template match="/">
  <!-- I don't actually know what to expect here so just pass it off. -->
  <xsl:apply-templates select="./*"/>
</xsl:template>

<!-- Strip html wrapper if it exists. -->
<xsl:template match="html | body" priority="2">
  <xsl:apply-templates select="./*"/>
</xsl:template>

<!-- remove these elements and all children. -->
<xsl:template match="style | head | title" priority="2">
</xsl:template>

<!-- The p class rules. Most of the transformation will generally happen here. -->
<xsl:template match='p' priority="2" >
    <xsl:choose>
    <!-- Format a Table of contents -->
    <xsl:when test="@class='MsoToc1' or @class='MsoToc2' or @class='MsoToc3' or @class='MosToc4'">
      <xsl:variable name='toc_class'>
        <xsl:choose>
          <xsl:when test="@class='MsoToc1'">toc-1</xsl:when>
          <xsl:when test="@class='MsoToc2'">toc-2</xsl:when>
          <xsl:when test="@class='MsoToc3'">toc-3</xsl:when>
          <xsl:when test="@class='MsoToc4'">toc-4</xsl:when>
        </xsl:choose>
      </xsl:variable>
      <div class='toc {$toc_class}'>
        <xsl:for-each select="*//text()">
          <xsl:if test='string-length(.) &gt; 2'>
            <xsl:value-of select='.' />
          </xsl:if>
        </xsl:for-each>
      </div>
    </xsl:when>
    <!-- Reformat a top level title into its HTML element -->
    <xsl:when test="@class='MsoTitle'">
      <h1>
        <xsl:apply-templates />
      </h1>
    </xsl:when>
    <!-- Reformat a sub title into its HTML element -->
    <xsl:when test="@class='MsoSubtitle'">
      <h2>
        <xsl:apply-templates />
      </h2>
    </xsl:when>
    <!-- Reformat a block quote into its HTML element -->
    <xsl:when test="@class='blockquote' or @class='MsoBlockText'">
      <blockquote>
        <xsl:apply-templates />
      </blockquote>
    </xsl:when>
    <!-- ignore nbsp lines -->
    <xsl:when test="string-length(normalize-space()) &gt; 1">
      <p>
        <!-- Preserve styles -->
        <xsl:choose>
          <xsl:when test="string-length(normalize-space(@style)) &gt; 1">
            <xsl:attribute name="style"><xsl:value-of select="@style" /></xsl:attribute>
          </xsl:when>
        </xsl:choose>
        <xsl:apply-templates />
      </p>
    </xsl:when>
  </xsl:choose>
</xsl:template>

<!-- Convert proprietary semantic tags to spans with classes -->
<xsl:template match="
  st1:country-region |
  st1:place |
  street |
  address |
  place |
  city |
  country-region |
  personname |
  date |
  placetype |
  placename |
  state |
  sn
  " priority="3">
  <xsl:value-of select='.' />
</xsl:template>

<!-- By default, just pass the element through. -->
<xsl:template match="*">
  <xsl:element name="{name()}">
    <xsl:apply-templates />
  </xsl:element>
</xsl:template>


</xsl:stylesheet>
