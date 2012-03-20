require 'httparty'

class AvocadoDB
  include HTTParty

  base_uri 'http://localhost:8529'
  format :json

  def self.create_collection (name, wait_for_sync = true)
    body = "{ \"name\" : \"#{name}\", \"waitForSync\" : #{wait_for_sync} }"

    doc = self.post("/_api/database/collection", :body => body)

    if doc.code == 409
      return doc.parsed_response['id']
    end

    if doc.code != 200
      return nil
    end

    return doc.parsed_response['id']
  end

  def self.drop_collection (name)
  end

  def self.log (args)
    if args.key?(:output)
      logfile = File.new("#{args[:output]}.log", "a")
    else
      logfile = File.new("output.log", "a")
    end

    method = args[:method] || :get
    url = args[:url]
    body = args[:body]
    headers = args[:headers]
    result = args[:result]
    response = result.parsed_response

    logfile.puts '-' * 80

    h_option = ""
    h_sep = ""

    if headers
      for k in [ "if-match", "if-none-match" ] do
	if headers.key?(k)
	  h_option = h_option + h_sep + "'-H #{k}: #{headers[k]}'"
	  h_sep = " "
	end
      end
    end

    if method == :get
      logfile.puts "> curl -X GET #{h_option} --dump - http://localhost:8529#{url}"
	logfile.puts
    elsif method == :post
      if body == nil
	logfile.puts "> curl -X POST #{h_option} --dump - http://localhost:8529#{url}"
	logfile.puts
      else
	logfile.puts "> curl --data @- -X POST #{h_option} --dump - http://localhost:8529#{url}"
	logfile.puts body
	logfile.puts
      end
    else
      logfile.puts "MISSING"
    end

    logfile.puts "HTTP/1.1 #{result.code} #{result.message}"

    if result.headers.key?('content-type')
      logfile.puts "content-type: #{result.headers['content-type']}"
    end

    if result.headers.key?('location')
      logfile.puts "location: #{result.headers['location']}"
    end

    if result.headers.key?('etag')
      logfile.puts "etag: #{result.headers['etag']}"
    end

    if response != nil
      logfile.puts
      logfile.puts JSON.pretty_generate(response)
    end

    logfile.close
  end
end
