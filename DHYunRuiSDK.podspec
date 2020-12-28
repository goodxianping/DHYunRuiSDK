#
# Be sure to run `pod lib lint DHYunRuiSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'DHYunRuiSDK'
  s.version          = '0.1.0'
  s.summary          = 'A short description of DHYunRuiSDK.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/starryKey/DHYunRuiSDK'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'starryKey' => '1056838379@qq.com' }
  s.source           = { :git => 'https://github.com/starryKey/DHYunRuiSDK.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'
  s.vendored_frameworks ='DHYunRuiSDK/Depend/sdk_output/Framework/*.framework'
  s.frameworks = "VideoToolbox", "AudioToolbox", "CoreMedia"
#  s.libraries = "stdc++.6.0.9", "c++", "iconv", "z","resolv",'xml2'
  s.pod_target_xcconfig = { 'ENABLE_BITCODE' => 'false','CLANG_CXX_LIBRARY' => "libstdc++",'CLANG_WARN_DOCUMENTATION_COMMENTS' => 'NO','OTHER_LDFLAGS' => '-ObjC -all_load'}
  
  s.resources = 'DHYunRuiSDK/Depend/sdk_output/Bundle/*.bundle'
  s.public_header_files = 'DHYunRuiSDK/Depend/sdk_output/Headers/**/*.h'
  s.source_files = 'DHYunRuiSDK/Depend/sdk_output/Headers/**/*.h'
  
  s.dependency 'AFNetworking'
  
end
