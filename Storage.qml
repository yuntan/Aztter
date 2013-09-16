import QtQuick 2.0
import QtQuick.LocalStorage 2.0

Item {
    property var db

    Component.onCompleted: db = LocalStorage.openDatabaseSync("Aztter", "0.1", "Aztter twitter client database", 4*1024*1024);

    function isAuthenticated() {
        var r;
        db.transaction(function(tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS Accounts(screen_name TEXT PRIMARY KEY, oauth_token TEXT, oauth_token_secret TEXT)');
            r = tx.executeSql('SELECT * FROM Accounts');
        })
        if(r.rows.length)
            return true;
        else
            return false;
    }

    function screenName(index) {
        var r;
        db.transaction(function(tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS Accounts(screen_name TEXT PRIMARY KEY, oauth_token TEXT, oauth_token_secret TEXT)');
            r = tx.executeSql('SELECT * FROM Accounts');
        })
        if(index < r.rows.length)
            return r.rows.item(index)['screen_name'];
        else
            return "";
    }

    function oauthToken(index) {
        var r;
        db.transaction(function(tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS Accounts(screen_name TEXT PRIMARY KEY, oauth_token TEXT, oauth_token_secret TEXT)');
            r = tx.executeSql('SELECT * FROM Accounts');
        })
        if(index < r.rows.length)
            return  r.rows.item(index)['oauth_token'];
        else
            return "";
    }

    function oauthTokenSecret(index) {
        var r;
        db.transaction(function(tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS Accounts(screen_name TEXT PRIMARY KEY, oauth_token TEXT, oauth_token_secret TEXT)');
            r = tx.executeSql('SELECT * FROM Accounts');
        })
        if(index < r.rows.length)
            return r.rows.item(index)['oauth_token_secret'];
        else
            return "";
    }

    function addAccount(name, token, tokenSecret) {
        db.transaction(function(tx) {
            var r = tx.executeSql('INSERT OR REPLACE INTO Accounts VALUES (?, ?, ?)', [name, token, tokenSecret]);
            console.log("Account Infomation Saved");
        })
    }
}
