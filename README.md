
<HTML>
<HEAD>
<TITLE>Homework #6 - CSCI 531, Spring 2015</TITLE>
<LINK HREF="../../cs531bc.css" REL="stylesheet" TYPE="text/css">
<LINK REV="made" HREF="mailto:bill.cheng@acm.org"></HEAD>
<BODY BGCOLOR="#FFFFFF" LINK="#D02090" VLINK="#996600" ALINK="#990000">


The purpose of this assignment is to get familiar with
AES and arithematics in <I>GF(2<SUP>8</SUP>)</I>
by implementing AES-128 (Nk=4, Nb=4, Nr=10)
from scratch with the flexibility
of changing some of the internal tables.

</TR>
<TR><TD>&nbsp;</TD></TR>
<TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
        <FONT COLOR="#ffffff"><A
        NAME="compile"><B>Compiling</B></A></FONT>
    </TD>
</TR>
<PRE>
make hw6</PRE>
an executable named <B>hw6</B> is created.

<TR><TD>&nbsp;</TD></TR>
<!-- Section -->
<TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
        <FONT COLOR="#ffffff"><A
        NAME="syntax"><B>Commandline Syntax & Program
        Output</B></A></FONT>
    </TD>
</TR>
<!-- Top Section -->
<TR><TD COLSPAN=3 ALIGN=LEFT>
The commandline syntax for <B>hw6</B> is as follows:

<PRE>
    <B>hw6</B> <B>tablecheck</B> <B>-t=</B>tablefile
    <B>hw6</B> <B>modprod</B> <B>-p1=</B>poly1 <B>-p2=</B>poly2
    <B>hw6</B> <B>keyexpand</B> <B>-k=</B>key <B>-t=</B>tablefile
    <B>hw6</B> <B>encrypt</B> <B>-k=</B>key <B>-t=</B>tablefile [file]
    <B>hw6</B> <B>decrypt</B> <B>-k=</B>key <B>-t=</B>tablefile [file]
    <B>hw6</B> <B>inverse</B> <B>-p=</B>poly</PRE>

<P>

Square bracketed items are optional.
Follows the UNIX convention that <B>commandline options</B>
can come in any order.  (Note: a <B>commandline option</B> is a
commandline argument that begins with a <B>-</B> character in a
commandline syntax specification.)
If an input file is not specified, the program
reads from <TT>stdin</TT>.
Output of the program goes to <TT>stdout</TT> and
error messages go to <TT>stderr</TT>.

<P>

The meaning of the commands are:

<BLOCKQUOTE>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>tablecheck</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Check the integrity of <TT>tablefile</TT>.
                       Please see <A HREF="#format">tablefile format</A>
                       to see the requirements.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>modprod</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Perform <B>modular product</B>
                       (modulo {01}x<SUP>4</SUP>+{01})
                       of two polynomials
                       with coefficients in <I>GF(2<SUP>8</SUP>)</I>.
                       (Please see equation (4.11) and (4.12)
                       on page 13 of FIPS-197
                       to see how to perform modular product.)
                       This is referred to as the <B>circle X</B>
                       operation in lecture slides.
                       The coefficients of the polynomials are represented
                       as hexstrings in <TT>poly1</TT> and <TT>poly2</TT>
                       (each hexstring has a string length of 8).
                       The first two hex digits correspond to the coefficient
                       for <I>x<SUP>3</SUP></I>,
                       the next two hex digits correspond to the coefficient for
                       <I>x<SUP>2</SUP></I>, etc.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>keyexpand</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Perform the key expansion algorithm for AES-128
                       using <TT>key</TT> as the 16-byte cipher key
                       in hexstring format (32 characters long).
                       Please use the s-box in <TT>tablefile</TT>.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>encrypt</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Encrypts the first 16 bytes of the input using AES-128
                       driven by
                       <TT>tablefile</TT> in the ECB mode using <TT>key</TT>
                       as the encryption key
                       (16 bytes long and in hexstring format).
                       If the filesize of the input is less than 16 bytes,
                       please print an error message.
                       (Please treat the input as a binary file.)
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>decrypt</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Decrypts the first 16 bytes of the input using AES-128
                       driven by
                       <TT>tablefile</TT> in the ECB mode using <TT>key</TT>
                       as the encryption key
                       (16 bytes long and in hexstring format).
                       If the filesize of the input is less than 16 bytes,
                       please print an error message.
                       (Please treat the input as a binary file.)
                       <P>
                       Please note that you must <B>not</B> use the
                       <I>Equivalent Inverse Cipher
                       (section 5.3.5 of FIPS-197)</I> implementation
                       because grading requires that you print out the
                       intermediate values from the standard
                       <I>Inverse Cipher</I>.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>inverse</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Calculate the <B>multiplicative inverse</B>
                       (modulo {01}x<SUP>4</SUP>+{01})
                       of the polynomial <TT>poly</TT>
                       with coefficients in <I>GF(2<SUP>8</SUP>)</I> using
                       the <I>extended Euclidean algorithm</I>.
                       Although there are various ways of implementing the
                       extended Euclidean algorithm, you are required to use the
                       <A HREF="http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#The_table_method">
                       Table Method</A> for this assignment.
                       The Table Method for polymonials with coefficients
                       in <I>GF(2<SUP>8</SUP>)</I> is described on
                       <A HREF="../../lectures.html#aes">
                       slide 36 of the AES slides</A>.
        </TD>
    </TR>
</TABLE>
</BLOCKQUOTE>

<P>

The output for various commands are as follows.

<BLOCKQUOTE>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>tablecheck</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The command should produce no output in <TT>stdout</TT>.
            All error output must go to <TT>stderr</TT>.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>modprod</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The command should output
            <TT>poly1 CIRCLEX poly2 = poly3</TT> where <TT>poly3</TT> is the
            modular product of <TT>poly1</TT> and <TT>poly2</TT>, and
            each coefficient of a polynomial
            is printed as <TT>{XX}</TT> where <TT>XX</TT> is a hexstring
            representing a single byte of data.
            The first two hex digits correspond to the coefficient for
            <I>x<SUP>3</SUP></I>,
            the next two hex digits correspond to the coefficient for
            <I>x<SUP>2</SUP></I>, etc.  For example, if
            <TT>poly1</TT> is <TT>03010102</TT> and
            <TT>poly2</TT> is <TT>0b0d090e</TT>,
            the output should be:
    <PRE>
  {03}{01}{01}{02} CIRCLEX {0b}{0d}{09}{0e} = {00}{00}{00}{01}</PRE>
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>keyexpand</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The command should output all the 44 round keys.
            Each round key is 4 bytes long and in hexstring format.
            If the key index is only one digit, please use a blank space
            before it.  The following is an example showing the required
            format:
    <PRE>
  w[ 0]: 2b7e1516
  w[ 1]: 28aed2a6
  w[ 2]: abf71588
  ...
  w[41]: c9ee2589
  w[42]: e13f0cc8
  w[43]: b6630ca6</PRE>
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>encrypt</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The output of this command should look like page 36 of the
            <A HREF="../../papers.html#aes">FIPS 197 AES specification</A>.
            Please see page 35 of the FIPS-197 document regarding the
            definitions of the lines.  Below is an example:
    <PRE>
  round[ 0].input    00112233445566778899aabbccddeeff
  round[ 0].k_sch    000102030405060708090a0b0c0d0e0f
  round[ 1].start    00102030405060708090a0b0c0d0e0f0
  round[ 1].s_box    63cab7040953d051cd60e0e7ba70e18c
  round[ 1].s_row    6353e08c0960e104cd70b751bacad0e7
  round[ 1].m_col    5f72641557f5bc92f7be3b291db9f91a
  round[ 1].k_sch    d6aa74fdd2af72fadaa678f1d6ab76fe
  ...
  round[10].start    bd6e7c3df2b5779e0b61216e8b10b689
  round[10].s_box    7a9f102789d5f50b2beffd9f3dca4ea7
  round[10].s_row    7ad5fda789ef4e272bca100b3d9ff59f
  round[10].k_sch    13111d7fe3944a17f307a78b4d2b30c5
  round[10].output   69c4e0d86a7b0430d8cdb78070b4c55a</PRE>
            Please note that there are 4 spaces between the left
            and the right column, except for the last line where there are
            only 3 spaces separating the columns.
        </TD>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>decrypt</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The output of this command should look like pages 36 and 37 of the
            <A HREF="../../papers.html#aes">FIPS 197 AES specification</A>.
            Please see page 35 of the FIPS-197 document regarding the
            definitions of the lines.  Below is an example:
    <PRE>
  round[ 0].iinput   69c4e0d86a7b0430d8cdb78070b4c55a
  round[ 0].ik_sch   13111d7fe3944a17f307a78b4d2b30c5
  round[ 1].istart   7ad5fda789ef4e272bca100b3d9ff59f
  round[ 1].is_row   7a9f102789d5f50b2beffd9f3dca4ea7
  round[ 1].is_box   bd6e7c3df2b5779e0b61216e8b10b689
  round[ 1].ik_sch   549932d1f08557681093ed9cbe2c974e
  round[ 1].ik_add   e9f74eec023020f61bf2ccf2353c21c7
  ...
  round[10].istart   6353e08c0960e104cd70b751bacad0e7
  round[10].is_row   63cab7040953d051cd60e0e7ba70e18c
  round[10].is_box   00102030405060708090a0b0c0d0e0f0
  round[10].ik_sch   000102030405060708090a0b0c0d0e0f
  round[10].ioutput  00112233445566778899aabbccddeeff</PRE>
            Please note that there are 3 spaces between the left
            and the right column, except for the last line where there are
            only 2 spaces separating the columns.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>inverse</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The command should output the trace of the execution of the
            Table Method version of the extended Euclidean algorithm.
            At step <I>i</I> (<I>i &ge; 3)</I>,
            you need to make the coefficient for
            <I>x<SUP>&nbsp;6 - i</SUP></I> in <I>rem[i]</I> to be <I>{00}</I>
            (except when <I>i = 6</I>, then you need
            to make it to be <I>{01}</I>).  At the end of iteration <I>i</I>,
            you should check to see if <I>rem[i]</I> is zero (i.e., all coefficients are <I>{00}</I>).
            If it is, then you terminate and say that there is no inverse.
            <P>
            Below is an example with <TT>poly</TT> being <TT>03010102</TT>:
    <PRE>
  i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}
  i=2, rem[i]={03}{01}{01}{02}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{01}
  i=3, rem[i]={00}{a4}{a5}{a5}, quo[i]={00}{00}{f6}{52}, aux[i]={00}{00}{f6}{52}
  i=4, rem[i]={00}{00}{4f}{c5}, quo[i]={00}{00}{8a}{4f}, aux[i]={00}{8f}{40}{45}
  i=5, rem[i]={00}{00}{00}{9a}, quo[i]={00}{00}{f3}{ca}, aux[i]={09}{78}{26}{cd}
  i=6, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{a8}{05}, aux[i]={0b}{0d}{09}{0e}
  Multiplicative inverse of {03}{01}{01}{02} is {0b}{0d}{09}{0e}</PRE>
            Below is an example with <TT>poly</TT> being <TT>01020102</TT>
            where it does not have a multiplicative inverse:
    <PRE>
  i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}
  i=2, rem[i]={01}{02}{01}{02}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{01}
  i=3, rem[i]={00}{05}{00}{05}, quo[i]={00}{00}{01}{02}, aux[i]={00}{00}{01}{02}
  i=4, rem[i]={00}{00}{00}{00}, quo[i]={00}{00}{52}{a4}, aux[i]={00}{52}{00}{52}
  {01}{02}{01}{02} does not have a multiplicative inverse.</PRE>
            Please note that if the degree of <TT>poly</TT> is less than 3
            or the degree of <I>rem[i]</I> does not decrease by exactly 1 in each step,
            the above algorithm would <B>not</B> work without a minor adjustment.
            If the degree of <I>rem[i-1]</I> is <B>j</B> and the degree of <I>rem[i]</I> is <B>k</B>,
            the quotient will be a polynomial of degree <B>j - k</B>.  (The above case corresponds to
            the case where k is always j - 1 and the algorithm would terminate at the end of iteration 6.)
            With the adjustment, the algorithm may terminate before iteration 6.
            <P>
            Below is an example with <TT>poly</TT> being <TT>00020202</TT>:
    <PRE>
  i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}
  i=2, rem[i]={00}{02}{02}{02}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{01}
  i=3, rem[i]={00}{00}{01}{01}, quo[i]={00}{8d}{8d}{00}, aux[i]={00}{8d}{8d}{00}
  i=4, rem[i]={00}{00}{00}{02}, quo[i]={00}{00}{02}{00}, aux[i]={01}{01}{00}{01}
  i=5, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{8d}{00}, aux[i]={8d}{8d}{00}{8d}
  Multiplicative inverse of {00}{02}{02}{02} is {8d}{8d}{00}{8d}</PRE>
            <P>
            Here is another example with <TT>poly</TT> being <TT>00000201</TT>:
    <PRE>
  i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}
  i=2, rem[i]={00}{00}{02}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{01}
  i=3, rem[i]={00}{00}{00}{75}, quo[i]={8d}{cb}{e8}{74}, aux[i]={8d}{cb}{e8}{74}
  i=4, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{71}{00}, aux[i]={d7}{e6}{73}{b4}
  Multiplicative inverse of {00}{00}{02}{01} is {d7}{e6}{73}{b4}</PRE>
            <P>
            The following is the reverse of the previous example (<TT>poly</TT> is <TT>d7e673b4):
    <PRE>
  i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}
  i=2, rem[i]={d7}{e6}{73}{b4}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{01}
  i=3, rem[i]={00}{00}{00}{75}, quo[i]={00}{00}{ea}{75}, aux[i]={00}{00}{ea}{75}
  i=4, rem[i]={00}{00}{00}{01}, quo[i]={7e}{3f}{92}{fc}, aux[i]={00}{00}{02}{01}
  Multiplicative inverse of {d7}{e6}{73}{b4} is {00}{00}{02}{01}</PRE>
        </TD>
    </TR>
</TABLE>
</BLOCKQUOTE>

<P>

For your convenience, the multiplicative inverses of
<TT>{00}</TT> through <TT>{ff}</TT> in AES's finite field is
listed below.  (Clearly, <TT>{00}</TT> cannot have an inverse; but its
inverse is listed as <TT>{00}</TT> anyway.  It should not cause any
problem because it should never be accessed.)
    <PRE>
    00018df6cb527bd1e84f29c0b0e1e5c7
    74b4aa4b992b605f583ffdccff40eeb2
    3a6e5af1554da8c9c10a98153044a2c2
    2c45926cf3396642f235206f77bb5919
    1dfe37672d31f569a764ab135425e909
    ed5c05ca4c2487bf183e22f051ec6117
    165eafd349a63643f44791df3393213b
    79b7978510b5ba3cb670d006a1fa8182
    837e7f809673be569b9e95d9f702b9a4
    de6a326dd88a84722a149f88f9dc899a
    fb7c2ec38fb8654826c8124acee7d262
    0ce01fef11757871a58e763dbdbc8657
    0b282fa3dad4e40fa92753041bfcace6
    7a07ae63c5dbe2ea948bc4d59df8906b
    b10dd6ebc60ecfad084ed7e35d501eb3
    5b2338346846038cdd9c7da0cd1a411c</PRE>

</TD>
</TR>
<TR><TD>&nbsp;</TD></TR>
<!-- Section -->
<TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
<FONT COLOR="#ffffff"><A NAME="format">
<B><TT>tablefile</TT> Format</B></A></FONT>
</TD>
</TR>
<!-- Top Section -->
<TR><TD COLSPAN=3 ALIGN=LEFT>
A <TT>tablefile</TT> is an ASCII file containing exactly 3 lines.
Each line has the format of <TT>key=value</TT> where <TT>key</TT>
can be one of the following (must be in uppercase):
<B><TT>S</TT></B>,
<B><TT>P</TT></B>, and
<B><TT>INVP</TT></B>.
To the right of the equal sign, <TT>value</TT> contains
a single hexstring.
There should be no white spaces (such as space or tab characters).
The <TT>S</TT> line corresponds to the AES S-box in row major order.
The <TT>P</TT> line corresponds to the <I>a(x)</I> polynomial
in the <TT>MixColumns()</TT> transformation.
The <TT>INVP</TT> line corresponds to the <I>a<SUP>-1</SUP>(x)</I>
polynomial in the <TT>InvMixColumns()</TT> transformation.
The following are requirements for each of the tables (and corresponding
input lines).

<BLOCKQUOTE>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>S</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>This table contains a random permutation
                       of the values from 00 through ff, inclusive.
                       (You need to compute the inverse transform in your code.)
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>P</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>This table contains a hexstring of length 8 which
                       corresponds to 4 byte of binary values.  Each byte is a
                       coefficient of the <I>a(x)</I> polynomial
                       in the <TT>MixColumns()</TT> transformation.
                       The first two hex digits correspond to the coefficient
                       for <I>x<SUP>3</SUP></I>,
                       the next two hex digits correspond to the coefficient for
                       <I>x<SUP>2</SUP></I>, etc.
        </TD>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>INVP</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>This table contains a hexstring of length 8 which
                       corresponds to 4 byte of binary values.  Each byte is a
                       coefficient of the <I>a<SUP>-1</SUP>(x)</I> polynomial
                       in the <TT>InvMixColumns()</TT> transformation.
                       The first two hex digits correspond to the coefficient
                       for <I>x<SUP>3</SUP></I>,
                       the next two hex digits correspond to the coefficient for
                       <I>x<SUP>2</SUP></I>, etc.
        </TD>
    </TR>
</TABLE>
</BLOCKQUOTE>

</BODY>
</HTML>

