
<HTML>
<HEAD>
<TITLE>Homework #6 - CSCI 531, Spring 2015</TITLE>
<LINK HREF="../../cs531bc.css" REL="stylesheet" TYPE="text/css">
<LINK REV="made" HREF="mailto:bill.cheng@acm.org"></HEAD>
<BODY BGCOLOR="#FFFFFF" LINK="#D02090" VLINK="#996600" ALINK="#990000">

<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0 WIDTH=100%>
<TR><TD ALIGN=CENTER VALIGN=TOP WIDTH=112>
    <!-- COL 1, should be identical to all other pages here -->
    <TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0 WIDTH=113>
    <TR><TD ALIGN=CENTER VALIGN=TOP WIDTH=112>
        &nbsp;
        </TD>
    </TR>
    <TR><TD ALIGN=CENTER VALIGN=TOP WIDTH=112>
        <A HREF="http://www.cs.usc.edu/"><IMG SRC="../../images/usctommy.gif"
            ALT="USC CSD Home" BORDER=0></A>
        <!-- BR>&nbsp;<BR -->
        <!-- IMG SRC="images/small-uc.gif" BORDER=0 -->
        </TD>
    </TR>
    </TABLE>
    </TD>
    <!-- TD ALIGN=LEFT VALIGN=TOP WIDTH=13 -->
    <!-- COL 2, should be identical to all other pages here -->
        <!-- IMG SRC="images/spacer.gif" HEIGHT=1 WIDTH=13 -->
    <!-- /TD -->
    <TD ALIGN=LEFT VALIGN=TOP>
    <!-- COL 3, every page should be different -->
        <TABLE BORDER=0>
        <!-- Page Header -->
        <TR><TD ALIGN=LEFT VALIGH=TOP>
                <A HREF="../../">Spring 2015<A>
            </TD>
            <TD ALIGN=RIGHT VALIGH=TOP>
                <A HREF="../../">CSCI 531</A><BR>
            </TD>
        </TR>
        <BR>
        <!-- Page Title -->
        <TR><TD COLSPAN=3 ALIGN=CENTER>
                <H2>Homework #6</H2>
                <H4>(100 points total)</H4>
                <H2>AES-128</H2>
                <B><I>Due 11:45PM
                4/17/2015 (firm)</I></B>
                <!--
                <H3><FONT COLOR="red"><I>(Under Construction -
                    Anything Can Change without Notice)</I></FONT></H3>
                  -->
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A
                NAME="intro"><B>Assignment</B></A></FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
The purpose of this assignment is to get you familiar with
AES and arithematics in <I>GF(2<SUP>8</SUP>)</I>
by implementing AES-128 (Nk=4, Nb=4, Nr=10)
from scratch with the flexibility
of changing some of the internal tables.

<P>

Please see the
<A HREF="../../lectures.html#tentative">lecture slides on AES</A> or
the <A HREF="../../papers.html#aes">FIPS 197 AES specification</A>.

<P>

<A HREF="#submit">Electronic submissions</A> only.
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A
                NAME="compile"><B>Compiling</B></A></FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
Please use a <TT>Makefile</TT> so that when the grader simply enters:
    <PRE>
    make hw6</PRE>
an executable named <B>hw6</B> is created.
(Minor variation on the <TT>make</TT> command is allowed if it is
clearly documented in your <TT>README</TT> file.)
Please make sure that your submission conforms to
<A HREF="../../makefile.html#requirements">other
general compilation requirements</A>.
            </TD>
        </TR>
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
You must follow the UNIX convention that <B>commandline options</B>
can come in any order.  (Note: a <B>commandline option</B> is a
commandline argument that begins with a <B>-</B> character in a
commandline syntax specification.)
If an input file is not specified, your program must
read from <TT>stdin</TT>.
Output of your program must go to <TT>stdout</TT> and
error messages must go to <TT>stderr</TT>.

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

You can also calculate these values using either the
extended Euclidean algorithm or a brute
force method mentioned in class.  Or, if you prefer
just to hardcode this into a table, that would be
fine too.  You will need this table when you implement
the <B>inverse</B> command.

<P>

Please note that before encrypting or decrypting, your program
must make sure that the encryption key is valid and
call the <TT>tablecheck</TT> functionality internally to
make sure that you have a valid <TT>tablefile</TT> before proceeding.

<P>

Pleaes output reasonable and useful error messages if the command
is malformed or file does not exist or inaccessible.  If the key file
is malformed, please output meaningful error messages.
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
Please see the
<A HREF="../../lectures.html#tentative">lecture slides on AES</A> or
the <A HREF="../../papers.html#aes">FIPS 197 AES specification</A> for details.
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
In performing <B>tablecheck</B>, you must check if the product of
the polynomials represented by <B>P</B> and <B>INVP</B>
is <TT>{00}{00}{00}{01}</TT>.
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A
                NAME="testdata"><B>Test Data &amp; Sample Output</B></A>
                    </FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
The <TT>tablefile</TT> for the standard AES is provided as
<A HREF="aes.in"><TT>aes.in</TT></A>.  The standard AES
binary test vector (<TT>00112233445566778899aabbccddeeff</TT>)
is provided as <A HREF="testvec.in"><TT>testvec.in</TT></A>.
Another standard AES binary test vector
(<TT>3243f6a8885a308d313198a2e0370734</TT>)
is provided as <A HREF="testvec2.in"><TT>testvec2.in</TT></A>.

<P>

For the
<TT>"keyexpand -k=2b7e151628aed2a6abf7158809cf4f3c -t=aes.in"</TT>
command, the output should correspond to the round keys listed in
Appendix A.1 of the FIPS-197 document.

<P>

For the
<TT>"encrypt -k=2b7e151628aed2a6abf7158809cf4f3c -t=aes.in testvec2.in"</TT>
command, the states of the cipher should correspond to what's depicted in
Appendix B of the FIPS-197 document.

<P>

For the
<TT>"encrypt -k=000102030405060708090a0b0c0d0e0f -t=aes.in testvec.in"</TT>
command, the output of the cipher should correspond to what's depicted in
the <TT>CIPHER</TT> section in Appendix C.1 of the FIPS-197 document.
The output of the cipher should
be <TT>69c4e0d86a7b0430d8cdb78070b4c55a</TT> (the binary value is provided
in <A HREF="testvec.enc">testvec.enc</A>).

<P>

For the
<TT>"decrypt -k=000102030405060708090a0b0c0d0e0f -t=aes.in testvec.enc"</TT>
command, the output of the cipher should correspond to what's depicted in
the <TT>INVERSE CIPHER</TT> section in Appendix C.1 of the FIPS-197 document.
The output of the inverse cipher in this example should be identical
to <TT>testvec.in</TT>.
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A
                NAME="grading"><B>Grading Guidelines</B></A>
                    </FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
<!--
The grading guidelines is not available yet.
  -->

The <A HREF="hw6-grading.txt">grading guidelines</A> has been made available.
Please run the scripts in the guidelines on <TT>nunki.usc.edu</TT>.

<P>     
        
The grading guidelines is the <B>only</B> grading procedure we will use to
grade your program.  No other grading procedure will be used.
To the best of our effort, we will only change the testing data for
grading but not the commands.  (We may make minor changes if we discover
bugs in the script or things that we forgot to test.)  It is strongly
recommended that you run your code through the scripts in the grading guidelines.
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A
                NAME="misc"><B>Miscellaneous Requirements and Hints</B></A>
                    </FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
<UL>
<LI>If you use any publicly available AES-specific
    code or code that performs multiplication in <I>GF(2<SUP>8</SUP>)</I>,
    please make sure you give explicit credit in your code and also
    document it in your README file.
    One reference given in class was
    <A HREF="http://en.wikipedia.org/wiki/Finite_field_arithmetic#Program_examples">
    the code fragment here</A>.  I do not know if this works,
    please check it yourself to see if it's suitable.
<P>
<LI>Although there is no memory buffer size limit for this assignment, when
    reading an input file for encryption/decryption, please use a reasonable
    size file buffer.
<P>
<LI>It's important that <B>every byte</B> of your data is read and written
    correctly.  You will <B>lose a lot of points</B> if one byte of data is
    generated incorrectly!  The grading of this assignment will be <B>harsh</B>.
<P>
<LI>Please follow the UNIX convention that, when your output is an ASCII
    file, append '\n' in the last line of the output if it's not a
    blank line.  (This way, you don't get the commandline prompt appearing at
    the wrong place on the screen.)
<P>
<LI>String I/O functions such as <TT>fgets()</TT>, <TT>scanf()</TT>, and
    <TT>printf()</TT> are really meant for inputing/outputing
    null-terminated <I>strings</I>.
    Do <B>not</B> use them to input/output binary data!
<P>
<LI>The Solaris workstations in the ISD lab in SAL have the same
    setup as nunki.usc.edu.  So, if you are logged on to one of
    these workstations, please do your development locally and
    not to overload nunki unnecessarily.
<P>
<LI>Start working on this <B>early</B>!  Please don't complain
    to the instructor that this assignment is too tedious or
    it takes too much work just to parse the commandline.
    Get it done early and get it done right!
<P>
<LI>Hints on parsing a <TT>tablefile</TT>
    <A HREF="parsing.html">has been made available</A>.
</UL>
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A NAME="submit"><B>Submission</B></A></FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
All assignments are to be submitted electronically - including
your README file. To submit your work, you must first
<TT>tar</TT> all the files you want to submit into a <B>tarball</B> and
<TT>gzip</TT> it to create a <B>gzipped tarfile</B> named
<TT><B>hw6.tar.gz</B></TT>.  Then you upload
<TT><B>hw6.tar.gz</B></TT> to the
<A HREF="../../bsubmit.html">Bistro</A> system.
On <TT>nunki.usc.edu</TT> or <TT>aludra.usc.edu</TT>,
the command you can use to create a gzipped tarfile is:

    <PRE>
    /usr/usc/bin/gtar cvzf hw6.tar.gz MYFILES</PRE>

Where <B><TT>MYFILES</TT></B> is the list of file names that you are submitting
(you can also use wildcard characters if you are sure that it will pick up only
the right files).
<B>DO NOT</B> submit your compiled code, just your source code and
README file.  <B>Two point will be deducted</B> if you submit extra
binary files, such as <TT>hw6</TT>, <TT>.o</TT>,
<TT>core</TT>, or files that can be <B>generated</B> from the rest of your submission.

<P>
Please note that the 2nd commandline argument of the <TT>gtar</TT> command above
is the <B>output</B> filename of the <TT>gtar</TT> command.  So, if you omit
<TT>hw6.tar.gz</TT> above, you may accidentally replace one of your files with
the output of the <TT>gtar</TT> command.  So, please make sure that the
first commandline argument is <TT><B>cvzf</B></TT> and the 2nd commandline argument
is <TT><B>hw6.tar.gz</B></TT>.

<P>
In your README file, you should include the command that the grader
should use to compile your code to generate <B><TT>hw6</TT></B>.
If you don't include such instruction, the grader will assume that the command
specified in the spec should be used to compile your code.
But if they can't get your code to compile easily and you don't submit
compilation instructions, you will lose points.  Please also note that
you MUST include a README file in your submission.  If you have nothing
to put inside the README file, please write "(This file intentionally left blank.)"
in your README file.

<P>
Here are a couple of sample commands for creating your <TT>hw6.tar.gz</TT> file
(your command will vary depending on what files you want to submit):
    <PRE>
    /usr/usc/bin/gtar cvzf hw6.tar.gz *.c *.h Makefile README
    /usr/usc/bin/gtar cvzf hw6.tar.gz *.cpp *.h Makefile README.txt</PRE>

You should read the output of the above commands carefully to make sure
that <TT>hw6.tar.gz</TT> is created properly.
If you don't understand the output of the above commands, you need to learn
how to read it!  It's your responsibility to ensure that
<TT>hw6.tar.gz</TT> is created properly.

<P>
You need to run <A HREF="../../bsubmit.html"><B><TT>bsubmit</TT></B></A> to
submit hw6.tar.gz to the submission server.
Please use the following command:
    <PRE><B>
    ~csci551b/bin/bsubmit upload \
        -email `whoami`@usc.edu \
        -event merlot.usc.edu_80_1372906710_66 \
        -file hw6.tar.gz</B></PRE>

Please note that the quotation marks surrounding <TT>whoami</TT> are
<B>back-quote</B> characters and not single quotes.  It's best if
you just copy and paste the above command into your console and not
try to type the whole command in.

<P>

If the command is executed successfully, the output should look like the
<A HREF="../../bsubmit.html#normal">sample mentioned in the submission web page</A>.
If it doesn't look like that, please fix your command and rerun it until it looks
right.  If there are problems, please contact the instructor.

<P>
It is extreme important that you also <A HREF="../../submit.html#verify"><B>verify your submission</B></A>
after you have submitted <TT>hw6.tar.gz</TT> electronically to make
sure that everything you have submitted is everything you wanted us to grade.

<P>
Finally, please be familiar with the <A HREF="../../submit.html">Electronic Submission Guidelines</A>
and information on the <A HREF="../../bsubmit.html">bsubmit web page</A>.
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        </TABLE>
    </TD>
</TR>
</TABLE>

<HR>
[<I>Last updated Sat Jan 10 2015</I>] &nbsp;&nbsp;
[<I>Please see <A
HREF="../../copyright.html">copyright</A> regarding copying.</I>]

<!-- @(#)$Id: index.html,v 1.4 2015/01/10 23:43:54 william Exp $ -->

</BODY>
</HTML>

