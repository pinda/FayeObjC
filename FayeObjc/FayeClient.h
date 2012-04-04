/* The MIT License
 
 Copyright (c) 2011 Paul Crawford
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. */

//
//  FayeClient.h
//  FayeObjC
//
#ifdef __MAC_OS_X_VERSION_MAX_ALLOWED
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

#import "SRWebSocket.h"
enum _fayeStates {
  kWebSocketDisconnected,
  kWebSocketConnected,
  kFayeDisconnected,
  kFayeConnected  
} fayeStates;

// Bayeux protocol channels
#define HANDSHAKE_CHANNEL @"/meta/handshake"
#define CONNECT_CHANNEL @"/meta/connect"
#define DISCONNECT_CHANNEL @"/meta/disconnect"
#define SUBSCRIBE_CHANNEL @"/meta/subscribe"
#define UNSUBSCRIBE_CHANNEL @"/meta/unsubscribe"

@protocol FayeClientDelegate <NSObject>

- (void)messageReceived:(NSDictionary *)messageDict;
- (void)connectedToServer;
- (void)disconnectedFromServer;
@optional
- (void)socketDidSendMessage:(id)aWebSocket;
- (void)subscriptionFailedWithError:(NSString *)error;
- (void)subscribedToChannel:(NSString *)channel;

@end


@interface FayeClient : NSObject <SRWebSocketDelegate> {
  NSMutableArray *activeChannels;
  @private
  BOOL fayeConnected;  
  NSDictionary *connectionExtension;
}

@property (strong) NSString *fayeURLString;
@property (strong) SRWebSocket *webSocket;
@property (strong) NSString *fayeClientId;
@property (assign) BOOL webSocketConnected;
@property (strong) NSString *activeSubChannel;
@property (retain) NSMutableArray *activeChannels;
@property (retain) id <FayeClientDelegate> delegate;

- (id) initWithURLString:(NSString *)aFayeURLString channel:(NSString *)channel;
- (id) initWithURLString:(NSString *)aFayeURLString;
- (void) connectToServer;
- (void) connectToServerWithExt:(NSDictionary *)extension;
- (void) disconnectFromServer;
- (void) subscribeToChannel:(NSString*)channel;
- (void) unsubscribeFromChannel:(NSString*)channel;
- (void) unsubscribeFromChannels;
- (void) sendMessage:(NSDictionary *)messageDict;
- (void) sendMessage:(NSDictionary *)messageDict withExt:(NSDictionary *)extension;

@end
