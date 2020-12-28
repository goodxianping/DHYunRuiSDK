//
//  DHViewController.m
//  DHYunRuiSDK
//
//  Created by starryKey on 07/15/2020.
//  Copyright (c) 2020 starryKey. All rights reserved.
//

#import "DHViewController.h"
#import <DHSipSDK/SipMobileServerInfo.h>
#import "DSSVTSSOutGoingCallViewController.h"
#import "DSSCallViewController.h"
#import "DSSCallViewModule.h"
#import "DHDataCenter.h"
#import <DHSipSDK/SipManager.h>
#import <DHSipSDK/RemoteNotifyDefine.h>
#import <DHSipSDK/HttpAPI.h>
#import "NetWorkRequestMode.h"
#import "MBProgressHUD+Common.h"

@interface DHViewController ()<UITextFieldDelegate>
@property (weak, nonatomic) IBOutlet UITextField *sipAddTextfield;
@property (weak, nonatomic) IBOutlet UITextField *sipPortTextfield;
@property (weak, nonatomic) IBOutlet UITextField *phoneNumberTextField;

@property (weak, nonatomic) IBOutlet UITextField *clientIdTextfield;
@property (weak, nonatomic) IBOutlet UITextField *clientSecretTextfield;

@property (weak, nonatomic) IBOutlet UITextField *hybridCloudIPTextfield;
@property (weak, nonatomic) IBOutlet UITextField *hybridCloudPortTextfield;
@property (weak, nonatomic) IBOutlet UITextField *hybridCloudphoneTextfield;

@property (nonatomic, strong) DSSCallViewController *callInViewController;
@property (nonatomic, strong) DSSVTSSOutGoingCallViewController *callOutViewController;

@property (nonatomic, strong)DSSCallViewModule *viewModel;
@property (nonatomic, copy) NSString *token;
@end

@implementation DHViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    _viewModel = [[DSSCallViewModule alloc] init];

    self.sipAddTextfield.delegate = self;
    self.sipPortTextfield.delegate = self;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cscConnected) name:VT_CALL_ACTION_EVENT_REGISTER object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(incomingCall:) name:VT_CALL_ACTION_EVENT_INVITE object:nil];
    
}

- (void)requestToken {
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    NSDictionary *dic = @{@"clent_secret":self.clientSecretTextfield.text,
                          @"clent_id":self.clientIdTextfield.text
    };
    __weak typeof(self)weakself = self;
    [NetWorkRequestMode requestForTokenWithDic:dic success:^(NSDictionary * _Nonnull resultDic) {
        [hud hideAnimated:YES];
        weakself.token = resultDic[@"access_token"];
        [MBProgressHUD showToast:@"Login Success"];
    } failed:^(NSError * _Nonnull error) {
        [hud hideAnimated:YES];
        [MBProgressHUD showToast:@"Token请求失败"];
    }];
}

- (void)cscConnected{
    dispatch_async(dispatch_get_main_queue(), ^{
        
    });
}

#pragma mark - UITextFieldDelegate
- (void)textFieldDidEndEditing:(UITextField *)textField{
    NSLog(@"--->%@",textField.text);
    if (textField == self.sipAddTextfield) {
        self.sipAddTextfield.text = textField.text;
    }
    if (textField == self.sipPortTextfield) {
        self.sipPortTextfield.text = textField.text;
    }
}
- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

// 呼出
- (IBAction)callOutAction:(UIButton *)sender {
    DSSVTSSOutGoingCallViewController *callManageVC = [[DSSVTSSOutGoingCallViewController alloc] initWithNibName:@"DSSVTSSOutGoingCallViewController" bundle:[NSBundle mainBundle]];
    DSSVTSSOutGoingCallViewModule *callManageVM = [[DSSVTSSOutGoingCallViewModule alloc] init];
    callManageVC.viewModule = callManageVM;
    callManageVC.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:callManageVC animated:YES completion:nil];
}

- (void)incomingCall:(NSNotification *)notification{
    dispatch_async(dispatch_get_main_queue(), ^{
        //登录鉴权token
        [DHDataCenter shareInstance].token =self.token;
        //下级需要（下级呼叫时带的有）
        [DHDataCenter shareInstance].communityCode = @"b27ba7400d204bb488f2ea01b002cbb9";
        // 可为空
        [DHDataCenter shareInstance].userId = @"";
        // 服务地址
        [DHDataCenter shareInstance].serviceHost = self.sipAddTextfield.text;//@"siptest.cloud-dahua.com";
        // 公司ID
        [DHDataCenter shareInstance].companyID = @"10";
        // 人员ID
        [DHDataCenter shareInstance].personFileID = @"490540956573970432";
        // lcToken用于播放视频
        [DHDataCenter shareInstance].lcToken = @"Ut_0000474b228db13a49a7b911a1e51ffb";
        // 手机号
        [DHDataCenter shareInstance].phoneNumber = self.phoneNumberTextField.text;
        
        [[HttpAPI shareInstance] setHost:@"https://www.cloud-dahua.com/gateway"];
        [[HttpAPI shareInstance] setToken:self.token];
        
        DSSCallViewController *callVC = [[DSSCallViewController alloc] initWithNibName:@"DSSCallViewController" bundle:[NSBundle mainBundle]];
        DSSCallViewModule *callViewModel = [[DSSCallViewModule alloc] init];
        callVC.viewModule = callViewModel;
        [callVC configNotification:notification];
        callVC.modalPresentationStyle = UIModalPresentationFullScreen;
        [self presentViewController:callVC animated:YES completion:nil];
    });
}
- (IBAction)Login:(id)sender {
    [self requestToken];
}
- (IBAction)initSip:(id)sender {
    // 云平台
    NSNumber *cloudPersonSource = @1;
    SipMobileServerInfo* cloudSipInfo  = [[SipMobileServerInfo alloc] init];
    cloudSipInfo.expireTime            = 30; //信令超时时间
    cloudSipInfo.keepAliveTime         = 30; // 保活时间
    cloudSipInfo.localSipPort          = 37070; //任意本地端口
    cloudSipInfo.primarySipServer      = self.sipAddTextfield.text; // IP
    cloudSipInfo.serverSipPort         = [self.sipPortTextfield.text integerValue]; // 端口
    cloudSipInfo.account               = self.phoneNumberTextField.text; // 账户
    // SN呼入时拿到
    cloudSipInfo.userAgent             = [NSString stringWithFormat: @"%@ SN:%@", @"APPClient", self.phoneNumberTextField.text];
    NSString *cloudUniqueKey = [NSString stringWithFormat:@"%@:%@",self.sipAddTextfield.text, self.sipPortTextfield.text];
    [[SipManager shareInstance] addSipserver:cloudSipInfo withKey:cloudUniqueKey changeContact:[cloudPersonSource boolValue]];
    
    // 混合云
    /*
    NSNumber *hybridCloudPersonSource = @0;
    SipMobileServerInfo* hybridCloudSipInfo  = [[SipMobileServerInfo alloc] init];
    hybridCloudSipInfo.expireTime            = 30; //信令超时时间
    hybridCloudSipInfo.keepAliveTime         = 30; // 保活时间
    hybridCloudSipInfo.localSipPort          = 37777; //任意本地端口
    hybridCloudSipInfo.primarySipServer      = self.hybridCloudIPTextfield.text;
    hybridCloudSipInfo.serverSipPort         = [self.hybridCloudPortTextfield.text integerValue]; // 5082
    hybridCloudSipInfo.account               = self.hybridCloudphoneTextfield.text;
    // SN呼入时拿到
    hybridCloudSipInfo.userAgent             = [NSString stringWithFormat: @"%@ SN:%@", @"APPClient", self.hybridCloudphoneTextfield.text];
    NSString *hybridCloudUniqueKey = [NSString stringWithFormat:@"%@:%@",self.hybridCloudIPTextfield.text, self.hybridCloudPortTextfield.text];
    [[SipManager shareInstance] addSipserver:hybridCloudSipInfo withKey:hybridCloudUniqueKey changeContact:[hybridCloudPersonSource boolValue]];
     */
}
- (IBAction)uninitSip:(id)sender {
    [[SipManager shareInstance] removeAll];
}
- (IBAction)callManager:(id)sender {
    NSString *cloudUniqueKey = [NSString stringWithFormat:@"%@:%@",self.sipAddTextfield.text, self.sipPortTextfield.text];
    DSSVTSSOutGoingCallViewController *callManageVC = [[DSSVTSSOutGoingCallViewController alloc] initWithNibName:@"DSSVTSSOutGoingCallViewController" bundle:[NSBundle mainBundle]];
    DSSVTSSOutGoingCallViewModule *callManageVM = [[DSSVTSSOutGoingCallViewModule alloc] initWithCommunityCode:@"b27ba7400d204bb488f2ea01b002cbb9" withUniqueKey:cloudUniqueKey];
    callManageVC.viewModule = callManageVM;
    callManageVC.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:callManageVC animated:YES completion:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
