/**
 *  @file   scripts.js
 *
 *  Sunsys Dox JavaScript library for IE & Mozilla.
 *
 *
 *  Copyright (C) Supernar Systems, Ltd. 2000-2005
 *  All Rights Reserved.
 *
 *  @author     Narech Koumar
 *  @version    1.6.0
 */

var ie4 = document.all;
var ns4 = document.layers;
var ns6 = document.getElementById && !document.all;

var imgWinOpened    = "resources/winO.png";
var imgWinClosed    = "resources/winC.png";
var txtWinOpened    = "collapse";
var txtWinClosed    = "expand";

var imgFolderOpened = "resources/foldO.png";
var imgFolderClosed = "resources/foldC.png";
var txtFolderOpened = "collapse";
var txtFolderClosed = "expand";


function toggleWinTable(myEvent)
{
    if(!(ie4 || ns6))
        return;

    var skipCount = 1;
    var eventNode = ie4 ? event.srcElement : myEvent;
    var myElement = eventNode;

    while(myElement != null)
    {
        if(myElement.nodeName == "TABLE")
        {
            skipCount--;
            if(skipCount < 0)
                break;
        }
        myElement = myElement.parentNode;
    }
    if(myElement != null)
    {
        var myDisplay;

        if(eventNode.src.search(imgWinOpened) > -1)
        {
            eventNode.alt   = txtWinClosed;
            eventNode.src   = imgWinClosed;
            myDisplay       = "none";
        }
        else
        {
            eventNode.alt   = txtWinOpened;
            eventNode.src   = imgWinOpened;
            myDisplay       = ie4 ? "block" : "table-row";
        }
        for(i = 1; i < myElement.rows.length; i++)
        {
            myElement.rows[i].style.display = myDisplay;
        }
    }
}

function toggleWinTable2(myEvent)
{
    if(!(ie4 || ns6))
        return;

    var skipCount = 1;
    var eventNode = ie4 ? event.srcElement : myEvent;
    var myElement = eventNode;

    while(myElement != null)
    {
        if(myElement.nodeName == "TABLE")
        {
            skipCount--;
            if(skipCount < 0)
                break;
        }
        myElement = myElement.parentNode;
    }
    if(myElement != null)
    {
        var myDisplay;

        if(eventNode.src.search(imgWinOpened) > -1)
        {
            eventNode.alt   = txtWinClosed;
            eventNode.src   = imgWinClosed;
            myDisplay       = "none";

            if(ie4)
            {
                var myCollection = myElement.all.tags("IMG");
                for(i = 0; i < myCollection.length; i++)
                {
                    if(myCollection[i].src.search(imgFolderClosed) > -1)
                    {
                        myCollection[i].alt = txtFolderOpened;
                        myCollection[i].src = imgFolderOpened;
                    }
                }
            }
            else
            {
                for(i = 1; i < myElement.rows.length; i++)
                {
                    for(j = 0; j < myElement.rows[i].cells.length; j++)
                    {
                        for(k = 0; k < myElement.rows[i].cells[j].childNodes.length; k++)
                        {
                            if(myElement.rows[i].cells[j].childNodes[k].nodeName == "IMG")
                            {
                                myElement.rows[i].cells[j].childNodes[k].alt = txtFolderOpened;
                                myElement.rows[i].cells[j].childNodes[k].src = imgFolderOpened;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            eventNode.alt   = txtWinOpened;
            eventNode.src   = imgWinOpened;
            myDisplay       = ie4 ? "block" : "table-row";
        }
        for(var i = 1; i < myElement.rows.length; i++)
        {
            myElement.rows[i].style.display = myDisplay;
        }
    }
}

function toggleFolderTable(myEvent, myId)
{
    if(!(ie4 || ns6))
        return;

    var skipCount = 0;
    var eventNode = ie4 ? event.srcElement : myEvent;
    var myElement = eventNode;

    while(myElement != null)
    {
        if(myElement.nodeName == "TABLE")
        {
            skipCount--;
            if(skipCount < 0)
                break;
        }
        myElement = myElement.parentNode;
    }
    if(myElement != null)
    {
        var myDisplay;

        if(eventNode.src.search(imgFolderOpened) > -1)
        {
            eventNode.alt   = txtFolderClosed;
            eventNode.src   = imgFolderClosed;
            myDisplay       = "none";
        }
        else
        {
            eventNode.alt   = txtFolderOpened;
            eventNode.src   = imgFolderOpened;
            myDisplay       = ie4 ? "block" : "table-row";
        }

        var i = 1;
        while(i < myElement.rows.length)
        {
            if(myElement.rows[i].id == myId)
                break;
            i++;
        }
        i++;
        while(i < myElement.rows.length)
        {
            if(myElement.rows[i].id != myId)
                break;
            myElement.rows[i].style.display = myDisplay;
            i++;
        }
    }
}

function setWindowTitle(myTitle)
{
    parent.document.title = myTitle;
}

function textReverse(inText)
{
    var r = "";
    var l = inText.length;
    while(l > 0)
    {
        r += inText.substring(l-1, l);
        l--;
    }
    return r;
}
function emailDescramble(inText)
{
    var t = inText.substr(1, inText.length-2);
    var r = textReverse(t);
    location.href = r;
}
function emailScramble(inText)
{
    var t = "@" + inText + "@";
    var r = textReverse(t);
    messageWindow=window.open("","displayWindow","menubar=no,scrollbars=no,status=yes,width=300,height=100");
    messageWindow.document.write("<html><head><\/head><body>");
    messageWindow.document.write("<center><br>" + r + "<br><\/center>");
    messageWindow.document.write("<\/body><\/html>");
}


/* EOF */
