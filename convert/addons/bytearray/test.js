load('../test-common.js');

function test1()
{
    var ba = new ByteArray(10);
    print('ba='+ba);
    ba[0] = 72; ba[1]=105;
    print('as string: '+ba.stringValue());
    ba.destroy();
    ba = new ByteArray("hi, world");
    print("new ba="+ba+': '+ba.stringValue());
    var i, b2;
    for( i = 0; i < 3; ++i ) {
        b2 = new ByteArray("!");
        ba.append(b2);
        b2.destroy();
    }
    print("Appended ba ("+ba.length+" bytes): "+ba.stringValue());
    for( i = 0; i < 3; ++i ) {
        ba.append("?");
    }
    print("Appended ba ("+ba.length+" bytes): "+ba.stringValue());
    for( i = 0; i < 3; ++i ) {
        ba.append(42 /* '*' */);
    }
    print("Appended ba ("+ba.length+" bytes): "+ba.stringValue());
    b2 = new ByteArray(ba);
    asserteq( ba.length, b2.length );
    ba.destroy();
    b2.destroy();
}

function testGZip()
{
    print("Starting gzip tests...");
    var ba = new ByteArray();
    var i;
    for( i = 0; i < 10; ++i ) ba.append("Line #"+i+"\n");
    var origString = ba.stringValue();
    var z = new ByteArray();
    var rc = ba.gzipTo(z);
    print("gzipTo() rc = "+rc);
    print("ba.length="+ba.length+", z.length="+z.length);
    assertneq( ba.length, z.length );
    print("First few bytes of z:");
    var li = [];
    for( i = 0; i < 5; ++i ) {
        li.push( z[i] );
    }
    print( JSON.stringify(li) );
    var u = new ByteArray();
    rc = z.gunzipTo(u);
    print("Unzip rc="+rc+", u.length="+u.length);
    asserteq( ba.length, u.length );
    print("Unzipped data:\n"+u.stringValue());
    var z2 = ba.gzip();
    asserteq( z2.length, z.length );
    u.destroy();
    z.destroy();

    u = z2.gunzip();
    z2.destroy;
    asserteq( ba.length, u.length );
    ba.destroy();
    asserteq( origString===u.stringValue(), true );
    u.destroy();
}


test1();
testGZip();
